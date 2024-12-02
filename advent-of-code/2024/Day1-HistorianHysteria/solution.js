const fs = require('fs');
const readline = require('readline');

function part1(leftList, rightList) {

    leftList = leftList.sort();
    rightList = rightList.sort();

    let sum = 0;
    

    for (let i = 0; i < leftList.length; i++) {
        sum += Math.abs(leftList[i] - rightList[i]);
    }

    console.log("🚀 ~ solution ~ sum:", sum)

    return sum;

}

function part2(leftList, rightList) {
    let hist = {};
    rightList.forEach((num) => {
        if (hist[num]) {
            hist[num]++;
        } else {
            hist[num] = 1;
        }
    });

    let sum = 0;
    leftList.forEach((num) => {
        if (hist[num]) {
          sum += num * hist[num];
        } 
    });
    console.log("🚀 ~ part2 ~ sum:", sum)
    return sum;
}
    

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
    const leftList = [];
    const rightList = [];
    for await (const line of rl) {
        const [left, right] = line.replace(/\s+/g, ' ').split(' ')
        leftList.push(parseInt(left));
        rightList.push(parseInt(right));
    }
    return part2(leftList, rightList);
  }

  
  processLineByLine();

  
