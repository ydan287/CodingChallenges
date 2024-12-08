const fs = require('fs');
const readline = require('readline');

function getAntenasLocations(puzzle) {
  const antenas = {};
  for (let i = 0; i < puzzle.length; i++) {
      for (let j = 0; j < puzzle[i].length; j++) {
          // if (puzzle[i][j] !== '1') {
          //   puzzle[i][j] = '.';
          // }
          if (puzzle[i][j] !== '.') {
              if (antenas[puzzle[i][j]]) {
                antenas[puzzle[i][j]].push([i, j]);  
              } else {
                antenas[puzzle[i][j]] = [[i, j]];
              }
          }
      }
  }
  return antenas;
}

function inBounds(i, j, puzzle) {
  return i >= 0 && i < puzzle.length && j >= 0 && j < puzzle[0].length;
}

function part1(puzzle) {
  
  const antenasLocations = getAntenasLocations(puzzle);
  const newAntenasLocations = new Set();
  const entries = Object.entries(antenasLocations);
  for (let i = 0; i < entries.length; i++) {
    const [antena, locations] = entries[i];
    // console.log("🚀 ~ part1 ~ antena, locations", antena, locations)
    for (let i = 0; i < locations.length; i++) {
      for (let j = i + 1; j < locations.length; j++) {
        let [l1i, l1j] = locations[i];
        newAntenasLocations.add(`${l1i},${l1j}`);
        let [l2i, l2j] = locations[j];
        newAntenasLocations.add(`${l2i},${l2j}`);
        let di = Math.abs(l1i - l2i);
        let dj = l1j - l2j;
        let n1j = l1j + dj;
        let n1i = Math.min(l1i, l2i) - di;
        let n2j = l2j - dj;
        let n2i = Math.max(l1i, l2i) + di;
        
        while(inBounds(n1i, n1j, puzzle)) {
          newAntenasLocations.add(`${n1i},${n1j}`);
          puzzle[n1i][n1j] = '#';
          n1j += dj;
          n1i -= di;
        }
        while(inBounds(n2i, n2j, puzzle)) {
          newAntenasLocations.add(`${n2i},${n2j}`);
          puzzle[n2i][n2j] = '#';
          n2j -= dj;
          n2i += di;
        }
      }
    }
    
  }
  
  puzzle.forEach(row => console.log(row.join('')))
  return newAntenasLocations.size
}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    const puzzle = [];
    
    for await (const line of rl) {
        puzzle.push(line.split(''))
    }

    console.log("🚀 ~ processLineByLine ~ puzzle:", part1(puzzle))
}

     

  
  processLineByLine();

  
