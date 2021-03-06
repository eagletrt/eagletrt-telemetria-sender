import { expect } from 'chai';
import { deserialize } from 'bson';
import { AsyncClient as MqttClient, connectAsync } from 'async-mqtt';
import { clean } from 'mongo-cleaner';
import { CanSimulatorInstance, GpsSimulatorInstance, simulateCan, simulateGps, virtualizeCan } from '@eagletrt/telemetria-simulator';
import { wait } from '../../utils/misc';
import { startTelemetry, TelemetryProcessInstance } from '../../utils/telemetry';
import getConfiguration from '../../utils/config';

const config = getConfiguration();

let
    canSimulatorInstance: CanSimulatorInstance,
    gpsSimulatorInstance: GpsSimulatorInstance,
    telemetryProcessInstance: TelemetryProcessInstance,
    mqttClient: MqttClient,
    mqttData: any;

export default async function () {
    describe('Test if can messages are sent with the right id', async function () {
        this.timeout(0);

        beforeEach(async function () {
            // Set telemetry config
            config.set({
                'mongodb.db': 'telemetry_test',
                'mongodb.collection': 'chimera_test',
            });

            // Connect to mqtt
            mqttData = [];
            mqttClient = await connectAsync(`mqtt://${config.data.mqtt.host}:${config.data.mqtt.port}`);
            await mqttClient.subscribe(config.data.mqtt.data_topic);
            mqttClient.on('message', (topic, message: Buffer) => {
                if (topic === config.data.mqtt.data_topic) {
                    mqttData.push(deserialize(message));
                }
            });

            // Virtualize can if not already virtualized
            await virtualizeCan(config.data.can_interface);
            // Simulate gps and get its interface
            gpsSimulatorInstance = await simulateGps();
            const gpsInterface = await gpsSimulatorInstance.getGpsInterface();


            // Set telemetry config
            config.set({
                'gps.plugged': 1,
                'gps.simulated': 1,
                'gps.interface': gpsInterface
            });

            // Start telemetry
            telemetryProcessInstance = await startTelemetry(config.path);

            // Simulate can
            await wait(1000);
            canSimulatorInstance = await simulateCan();
        })

        it('Should set all ids as 0 when in idle status', async function () {
            mqttData = [];
            await wait(4 * config.data.sending_rate);
            await telemetryProcessInstance.stop();
            const ids = mqttData.map(el => el.id);
            expect(ids).to.have.length.within(4, 5);
            expect(ids).to.satisfy((els: number[]) => {
                return els.every(el => el === 0);
            });
        });

        it('Should set all ids incremental and starting by 1 when in enabled status', async function () {
            const numberOfDocs = 15;
            telemetryProcessInstance.enable();
            await wait(config.data.sending_rate);
            mqttData = [];
            await wait(numberOfDocs * config.data.sending_rate);
            await telemetryProcessInstance.stop();
            const ids = mqttData.map(el => el.id) as number[];
            expect(ids).to.have.length.within(numberOfDocs - 1, numberOfDocs + 1, 'Not the right number of docs');
            while(ids[0] === 0) {
                ids.shift();
            }
            expect(ids).to.have.length.above(0, 'No ids greather than 0 found');
            expect(ids).to.satisfy((els: number[]) => {
                return els.every((el, index) => el === index + 1);
            }, 'Id not sequential');
            
        });

        afterEach(async function () {
            await gpsSimulatorInstance.stop();
            await canSimulatorInstance.stop();
            await mqttClient.end();
        });
    });
}