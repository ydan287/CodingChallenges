const fs = require('fs');
const readline = require('readline');

let metric = [];
let partNumbers = {}
async function processLineByLine() {
  const fileStream = fs.createReadStream('input.txt');

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity
  });
  for await (const line of rl) {
    metric.push(line);
  }
  // row, start, end
  let currentNumber = undefined;
    
  let sum = 0;
  let sumGears = 0
  for (let i = 0; i < metric.length; i++) {
    currentNumber = undefined;
    for (let j = 0; j <= metric[i].length; j++) {
        if (isDigit(metric[i][j])) {
            if (currentNumber === undefined) {
                // console.log('-----------------')
                currentNumber = [i, j, undefined];
                // console.log("currentNumber:", currentNumber)
            }
        } else {
            if (currentNumber !== undefined && currentNumber[2] === undefined) {
                currentNumber[2] = j - 1;
                if (checkNumber(currentNumber)) {
                    if(partNumbers[currentNumber[0]] === undefined) {
                        partNumbers[currentNumber[0]] = {[currentNumber[1]]: currentNumber[2]};
                    }else {
                        partNumbers[currentNumber[0]][currentNumber[1]] = currentNumber[2];
                    }
                    // console.log('valid number:', currentNumber);
                    sum += extractNumber(currentNumber);
                }
                else {
                    // console.log('invalid number:', currentNumber);
                }
                // console.log('-----------------')
                currentNumber = undefined;
            }
        }
    }
  }
  console.log('metric:\n', metric);
  console.log('partNumbers:', partNumbers);

  for (let i = 0; i < metric.length; i++) {
    for (let j = 0; j <= metric[i].length; j++) {
        gear = checkGear(i,j);
        if(gear) {
            console.log('gear:', gear);
            sumGears += gear;
        }
    }
  }
  console.log('sumGears:', sumGears);

}

function checkGear(i,j) {
    if (metric[i][j] !== '*') {
        return;
    }
    console.log('-----------------')
    console.log('checkGear:', i, j);
    let partNumbersCounter = 0;
    let gear = 1;
    // up
    for (let colI = j-1; colI <= j+1; colI++) {
        if (metric[i-1] && isDigit(metric[i-1][colI])) {
            partNumber = findPartNumber(i-1, colI);
            if (partNumber!==undefined) {
                const [row, start, end] = partNumber;
                partNumbersCounter++;
                gear *= extractNumber(partNumber);
                colI = end;
            }
        }
    }
    // down
    for (let colI = j-1; colI <= j+1; colI++) {
        if (metric[i+1] && isDigit(metric[i+1][colI])) {
            partNumber = findPartNumber(i+1, colI);
            if (partNumber!==undefined) {
                const [row, start, end] = partNumber;
                partNumbersCounter++;
                gear *= extractNumber(partNumber);
                colI = end;
            }
        }
    }
    // left
    if (metric[i] && isDigit(metric[i][j-1])) {
        partNumber = findPartNumber(i, j-1);
        if (partNumber!==undefined) {
            partNumbersCounter++;
            gear *= extractNumber(partNumber);
        }
    }
    // right
    if (metric[i] && isDigit(metric[i][j+1])) {
        partNumber = findPartNumber(i, j+1);
        if (partNumber!==undefined) {
            partNumbersCounter++;
            gear *= extractNumber(partNumber);
        }
    }
    console.log('partNumbers:', partNumbersCounter);
    if (partNumbersCounter === 2) {
        return gear;
    }
}

function findPartNumber(row, col) {
    if (partNumbers[row] === undefined) {
        return undefined;
    }
    let start = col;
    while(start >= 0) {
        if (partNumbers[row][start] !== undefined) {
            return [row, start, partNumbers[row][start]]
        }
        start--;
    }
    return undefined
};

function checkNumber(number) {
    const [row, start, end] = number;
    let vals = [];
    for (let rowI = row-1; rowI <= row+1; rowI++) {
        for (let colI = start-1; colI <= end+1; colI++) {
            if (metric[rowI] === undefined) {
                continue;
            }
            vals.push(metric[rowI][colI]);
            if (metric[rowI][colI] !== undefined && metric[rowI][colI] !== '.' && !isDigit(metric[rowI][colI])) {
                // console.log('symbol:', metric[rowI][colI], 'at', rowI, colI);
                return true;
            }
        }
        
    }
    // console.log('vals:', vals);
    return false;
}

function extractNumber(numberPoints){
    const [row, start, end] = numberPoints;
    number = parseInt(metric[row].substring(start, end+1))
    // console.log("number:", number)
    return number;
}

function isDigit(c) {
    return c >= '0' && c <= '9';
}


processLineByLine();