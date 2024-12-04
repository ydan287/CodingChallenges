const fs = require('fs');
const readline = require('readline');

function findInRows(puzzle) {
    console.log("🚀 ~ findInRows ~ puzzle:", puzzle)
    let sum = 0;
    
    for (let i = 0; i < puzzle.length; i++) {
        let row = puzzle[i];
        // console.log("🚀 ~ findInRows ~ row:\t\t", row)
        let matchs = row.match(/XMAS/g);
        if (matchs) {
            sum += matchs.length;
        }
        // console.log("🚀 ~ findInRows ~ sum:", sum)
        let reverseRow = row.split('').reverse().join('');
        // console.log("🚀 ~ findInRows ~ reverseRow:\t", reverseRow)
        matchs = reverseRow.match(/XMAS/g);
        if (matchs) {
            sum += matchs.length;
        }
        // console.log("🚀 ~ findInRows ~ sum:", sum)
    }
    console.log("🚀 ~ findInRows ~ sum:", sum)
    return sum;
}

function toCols(puzzle) {
    const newPuzzle = [];
    for (let row = 0; row < puzzle.length; row++) {
        
        for (let col = 0; col < puzzle[row].length; col++) {
            if (!newPuzzle[col]) {
                newPuzzle[col] = '';
            }
            newPuzzle[col] += puzzle[row][col];
        }
    
    }
    return newPuzzle;
}

function findInCols(puzzle) {
    
    return findInRows(toCols(puzzle));
}

function toDiags(puzzle) {
    const newPuzzle = [];
    for (let row = 0; row < puzzle.length; row++) {
        for (let col = 0; col < puzzle[row].length; col++) {
            if (!newPuzzle[col + row]) {
                newPuzzle[col + row] = '';
            }
            newPuzzle[col + row] += puzzle[row][col];
        }
    }
    return newPuzzle;
}

function findInDiags(puzzle) {
    return findInRows(toDiags(puzzle)) + findInRows(toDiags(puzzle.map(row => row.split('').reverse().join(''))));
}

function part1(puzzle) {
    return findInRows(puzzle) + findInCols(puzzle) + findInDiags(puzzle);
}

function isDiagMas(a, b) {
    return (a === 'M' && b === 'S') || (a === 'S' && b === 'M');
}

function part2(puzzle) {
    let sum = 0
    for (let i = 1; i < puzzle.length-1; i++) {
        for (let j = 1; j < puzzle[i].length-1; j++) {
            if (puzzle[i][j] === 'A' && isDiagMas(puzzle[i-1][j-1], puzzle[i+1][j+1]) && isDiagMas(puzzle[i-1][j+1], puzzle[i+1][j-1])) {
                sum++;
            }
        }
    }
    return sum;
}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    const puzzle = [];
    
    for await (const line of rl) {
        puzzle.push(line);
    }
     console.log("🚀 ~ processLineByLine ~ findXmas(puzzle):", part2(puzzle))
  }
     

  
  processLineByLine();

  
