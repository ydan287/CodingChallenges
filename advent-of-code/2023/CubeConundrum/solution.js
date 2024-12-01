const fs = require('fs');
const readline = require('readline');

const bag = {
    'red': 12,
    'blue': 14,
    'green': 13
}

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    let sum = 0;
    let counter = 0;
    for await (const line of rl) {
        counter++;
      
        const sets = parseLine(line)
        sum += setPower(sets)
        console.log('------------------')
    }
    console.log('sum: ',sum )
    
  }
  
  processLineByLine();

  setPower = (sets) => {
    minBug = {};
    
    sets.forEach(set => {
        Object.entries(set).forEach(([color, counter]) => {
            if (minBug[color] === undefined || minBug[color] < counter) {
                minBug[color] = counter;
            }
        });
    });
    let power = 1;
    Object.values(minBug).forEach(e => {
        power *= e;
        
    });
    console.log("minBug:", minBug)
    console.log("power:", power)
    return power;
  }

  parseLine = (line) => {
    console.log("🚀 line:", line)
    const countAndColors = line.split(':')[1];
    const rawSets = countAndColors.split(';');
    const sets = [];

    rawSets.forEach(rawSet => {
        set = {}; 
        rawSet.split(',').forEach(e => {
            const [counter, color] = e.trim().split(' ');
            // console.log(counter, color);
            set[color] = parseInt(counter);
        });
        sets.push(set);
        
    });
    console.log("🚀 sets:", sets)
    return sets;
  }

  checkSets = (sets) => {
    let result = true;
    sets.forEach(set => {
        if (!checkSet(set)) {
            result = false;
        }
    });
    return result;
  };

  checkSet = (set) => {
    let result = true;
    Object.entries(set).forEach(([color, counter]) => {
        if (bag[color] < counter) {
            console.log('❌ color: ', color, ' counter: ', counter
            )
            result = false;
        }
    });
    return result;
  }