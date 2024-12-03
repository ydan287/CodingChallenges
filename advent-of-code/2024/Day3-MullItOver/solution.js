const fs = require('fs');
const readline = require('readline');

function part1(data) {
    let sum = 0;
        data.match(/mul\(([0-9]+,[0-9]+\))/g).map(match => match.replace(/mul\(/, '').replace(')', '').split(',')).forEach(([a,b]) => {
            sum += Number(a) * Number(b)
        });
        return sum;
}


async function processLineByLine() {
    fs.readFile('input.txt','utf8', (err, data) => {
        
        if (err) {
            console.error(err)
            return
        }
        let cleanData = '';
        while(true) {
            const firstDont = data.indexOf("don't()");
            if (firstDont === -1) {
                cleanData += data;
                break;
            }
            cleanData += data.slice(0, firstDont);
            
            data = data.slice(firstDont + 7);
            const nextDo = data.indexOf("do()");
            data = data.slice(nextDo);
            
        }
        
        result = part1(cleanData);
        console.log(result)
        
    });
        
        
  }

  
  processLineByLine();

  
