const fs = require('fs');
const readline = require('readline');

function recursive(sum, operands) {
  if (operands.length === 1) {
    return sum === operands[0];
  }
  const operandsWithPlus = [operands[0] + operands[1], ...operands.slice(2)];
  const operandsWithMult = [operands[0] * operands[1], ...operands.slice(2)];
  return recursive(sum, operandsWithPlus) || recursive(sum, operandsWithMult);
}

function recursive2(sum, operands) {
  if (operands.length === 1) {
    return sum === operands[0];
  }
  const operandsWithPlus = [operands[0] + operands[1], ...operands.slice(2)];
  const operandsWithMult = [operands[0] * operands[1], ...operands.slice(2)];
  const operandsWithConcat = [Number(operands[0].toString() + operands[1].toString()), ...operands.slice(2)];
  return recursive2(sum, operandsWithPlus) || recursive2(sum, operandsWithMult) || recursive2(sum, operandsWithConcat);
}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    const equations = [];
    

    for await (const line of rl) {
        const [sum, operands] = line.split(': ');
        equations.push([Number(sum), operands.split(' ').map(Number)]);
    }

    let sum = 0;
    for (let [s, operands] of equations) {
        if (recursive2(s, operands)) {
            sum+=s;
        }
    }

    console.log("🚀 ~ processLineByLine ~ sum", sum)

}

     

  
  processLineByLine();

  
