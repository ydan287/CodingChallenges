const fs = require('fs');
const readline = require('readline');

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    let times;
    let distances;
    let mul = 1;
    for await (const line of rl) {
        let splits = line.split(':');
        if (splits[0].trim() === 'Time') {
            times = splits[1].trim().split(' ').map(e => parseInt(e)).filter(e => !isNaN(e));
            console.log("🚀 ~ file: solution.js:17 ~ forawait ~ times:", times)
        }
        if (splits[0].trim() === 'Distance') {
            distances = splits[1].trim().split(' ').map(e => parseInt(e)).filter(e => !isNaN(e));
            console.log("🚀 ~ file: solution.js:20 ~ forawait ~ distances:", distances)
        }
        console.log('------------------')
    }

    for (let i = 0; i < times.length; i++) {
        let time = times[i];
        let distance = distances[i];
        console.log('time: ', time, '  distance: ', distance)
        let counter = 0;
        for (let j = 0; j < time; j++) {
            const result = j * (time-j)
            // console.log('j:', j, ' result: ', result)
            if(result > distance) {
                counter++;
            }
        }
        mul *= counter;
        console.log("🚀 ~ file: solution.js:41 ~ processLineByLine ~ mul:", mul)
    }
    
  }
  
  processLineByLine();

 