const fs = require('fs');
const readline = require('readline');

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    const hands = []
    for await (const line of rl) {
        const [hand, score] = line.split(' ')
    }
    
    
  }
  
  processLineByLine();

  
