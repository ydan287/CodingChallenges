
const fs = require('fs');
const readline = require('readline');

async function processLineByLine() {
  const fileStream = fs.createReadStream('input.txt');

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity
  });
  // Note: we use the crlfDelay option to recognize all instances of CR LF
  // ('\r\n') in input.txt as a single line break.
  let sum = 0;
  for await (const line of rl) {
    
    console.log('------------------')
    console.log("line:", line)
    editedLine = convertLine(line)
    console.log("editedLine:", editedLine)
    editedLine = convertLineReverse(editedLine)
    console.log("editedLine:", editedLine)
    // Each line in input.txt will be successively available here as `line`.
    let onlyDigits = editedLine.replace(/\D/g,'');
    console.log("onlyDigits:", onlyDigits)
    let twoDigits = onlyDigits[0] + onlyDigits[onlyDigits.length - 1];
    console.log("twoDigits:", twoDigits)
    sum += parseInt(twoDigits);
  }
  console.log(sum)
}

processLineByLine()
numbers = {
    'one': '1',
    'two': '2',
    'three': '3',
    'four': '4',
    'five': '5',
    'six': '6',
    'seven': '7',
    'eight': '8',
    'nine': '9'
}
function convertLine(line) {
    
    for (let i = 0; i <= line.length; i++) {
        if (['1','2','3','4','5','6','7','8','9'].includes(line[i-1])) {
            return line;
        }
        for (let j = 0; j <= i; j++) {
            slice = line.slice(j,i)
            // console.log("🚀 ~ file: solution.js:53 ~ convertLine ~ slice:", slice)
            if (numbers[slice]) {
                line = line.substring(0, j) + numbers[slice] + line.substring(i);
                return line;
            }
        }
        
    }
    return line
}

function convertLineReverse(line) {
    for (let i = line.length; i >= 0; i--) { 
        if (['1','2','3','4','5','6','7','8','9'].includes(line[i+1])) {
            return line;
        }
        for (let j = line.length; j >= i; j--) {
            slice = line.slice(i,j)
            if (numbers[slice]) {
                line = line.substring(0, i) + numbers[slice] + line.substring(j);
                return line;
            }
        }
        
    }
    return line
}