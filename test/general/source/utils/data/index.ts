function instanceOfEagleMessages(obj: any): boolean {
    return Array.isArray(obj);
}

function instanceOfEagleGroup(obj: any): boolean {
    return !Array.isArray(obj) && typeof obj === 'object';
}

async function mergeGroups(result: any, group: any): Promise<void> {
    for (const key in group) {
        const resultElement = result[key];
        const groupElement = group[key];

        if (instanceOfEagleGroup(resultElement) && instanceOfEagleGroup(groupElement)) {
            await mergeGroups(resultElement, groupElement);
        }
        else if (instanceOfEagleMessages(resultElement) && instanceOfEagleMessages(groupElement)) {
            const newElements = groupElement.sort((x, y) => x.timestamp - y.timestamp);
            resultElement.push(...newElements);
        }
    }
}

export async function parseRecords(records: any): Promise<any> {
    if (records && records.length) {
        const result = records[0];

        for (let i = 0; i < records.length; i++) {
            await mergeGroups(result, records[i]);
        }
        
        return result;
    }
    else {
        return null;
    }
}

export function getDeepProperty(object: any, key: string): any {
    let result = object;

    const keys = key.split('.');
    for (const key of keys) {
        result = result[key];
    }

    return result;
}