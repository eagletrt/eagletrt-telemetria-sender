import mongoServiceTests from './souites/mongo_services/mongo_services.test'

describe('EagleTRT Telemetria Partial Tests', async function() {
    await mongoServiceTests();
});