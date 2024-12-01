const fs = require('fs');
const { parse } = require('path');
const readline = require('readline');

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
    let maps = [];
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    let currentMap = [];
    let seeds;
    for await (const line of rl) {
        console.log('line: *', line, '*')
        if (line.startsWith('seeds')) {
            seeds = line.split(': ')[1].split(' ').map(e => parseInt(e));
            console.log(seeds)
            continue;
        }
        if (line.trim().length === 0 && !currentMap.length) {
            continue;
        } else if (line.trim().length === 0 && currentMap.length > 0) {
            // console.log('currentMap', currentMap)
            maps.push(currentMap);
            // console.log(maps)
            console.log('------------------')
            currentMap = [];
            continue;
        }
        if (line.endsWith(':')) {
            continue;
        }
        entry = line.split(' ').map(e => parseInt(e));
        // console.log('entry', entry)
        currentMap.push(entry);
    }
    maps.push(currentMap);
    // console.log(maps)
    console.log('------------------')
    
    // find minumum
    let min;

    // find min for range of seeds
    // for(let si = 0; si < seeds.length; si++) {
    //     let s = seeds[si];
    //     console.log('------------------')
    //     for (let i = 0; i < maps.length; i++) {
    //         let map = maps[i];
            
    //         for (let j = 0; j < map.length; j++) {
    //             let [destination, source, range] = map[j];
    //             if (s >= source && s < source + range) {
    //                 s = destination + (s - source);
    //                 break
    //             }
    //         }
    //         console.log('s: ', s, ' --- map counter: ', i)
    //     }
    //     if (min === undefined || s < min) {
    //         min = s;
    //     }   
        
    // }

    for (let mapIndex = 0; mapIndex < maps.length; mapIndex++) {
        const map = maps[mapIndex];
        
        map.sort((e1, e2) => {
          return e1[1] - e2[1]      
        })
        
        nextSeeds = [];
        for (let si = 0; si < seeds.length; si+=2) {
            const seedSource = seeds[si];
            const seedRange = seeds[si+1];
            
            for (let entryIndex = 0; entryIndex < map.length; entryIndex++) {
                let [destination, source, range] = map[entryIndex];
                if (seedSource + seedRange < source) {
                    nextSeeds.push(seedSource);
                    nextSeeds.push(seedRange);
                    break;
                } else if (seedSource < source) {
                    nextSeeds.push(seedSource);
                    nextSeeds.push(source - seedSource);
                    seedSource = source;
                } else if (seedSource >= source && seedSource + seedRange <= source + range) {
                    nextSeeds.push(destination + (seedSource - source));
                    nextSeeds.push(seedRange);
                    break;
                } else if (seedSource >= source && seedSource + seedRange > source + range) {
                    nextSeeds.push(destination + (seedSource - source));
                    nextSeeds.push((source + range) - seedSource);
                }
            }    
        }
        seeds = nextSeeds
        

    }

    console.log('min: ', min)


  }
  
  processLineByLine();