const fs = require('fs');
const readline = require('readline');

const N = 0;
const E = 1;
const S = 2;
const W = 3;

function stepForward(i, j, direction) {
    switch (direction) {
        case N:
            return [i - 1, j]
        case E:
            return [i, j + 1]
        case S:
            return [i + 1, j]
        case W:
            return [i, j - 1]
    }
}

function countX(puzzle) {
    let count = 0;
    for (let i = 0; i < puzzle.length; i++) {
        for (let j = 0; j < puzzle[i].length; j++) {
            if (puzzle[i][j] === 'X') {
                count++;
            }
        }
    }
    return count;
}

function findOfficer(puzzle) {
    for (let i = 0; i < puzzle.length; i++) {
        for (let j = 0; j < puzzle[i].length; j++) {
            if (puzzle[i][j] === '^') {
                return [i, j]
            }
        }
    }
}

function isInfiniteLoop(puzzle) {
    let [oi, oj] = findOfficer(puzzle);
    let direction = 0;
    const visited = new Set();
    while (true) {
        const [i, j] = stepForward(oi, oj, direction);
        if (i < 0 || i >= puzzle.length || j < 0 || j >= puzzle[i].length) {
            return false;
        }
        if (puzzle[i][j] === '#') {
            direction = (direction + 1) % 4;
        } else {
            if (visited.has(`${i},${j},${direction}`)) {
                return true;
            }
            visited.add(`${i},${j},${direction}`);
            oi = i;
            oj = j;
        }
    }
}

function solution(puzzle) {
    // console.log("🚀 ~ solution ~ puzzle:", puzzle)
    let [oi, oj] = findOfficer(puzzle);
    let direction = 0;
    while (true) {
        const [i, j] = stepForward(oi, oj, direction);
        if (i < 0 || i >= puzzle.length || j < 0 || j >= puzzle[i].length) {
            puzzle[oi][oj] = 'X';
            break;
        }
        if (puzzle[i][j] === '#') {
            direction = (direction + 1) % 4;
        } else {
            puzzle[oi][oj] = 'X';
            oi = i;
            oj = j;
        }
    }
    // console.log("🚀 ~ solution ~ puzzle:", puzzle)

    return countX(puzzle);
}

function solution2(puzzle) {
    let [oi, oj] = findOfficer(puzzle);
    let direction = 0;
    let positions = new Set();
    while (true) {
        const [i, j] = stepForward(oi, oj, direction);
        if (i < 0 || i >= puzzle.length || j < 0 || j >= puzzle[i].length) {
            break;
        }
        if (puzzle[i][j] === '#') {
            direction = (direction + 1) % 4;
        } else {
            let temp = puzzle[i][j];
            puzzle[i][j] = '#'
            if (temp!== '^' && isInfiniteLoop(puzzle)) {
                positions.add(`${i},${j}`);
            }
            puzzle[i][j] = temp;
            oi = i;
            oj = j;
        }
    }
    return positions.size;
}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    const puzzle = []

    for await (const line of rl) {
        puzzle.push(line.split(''));
    }

    console.log(solution2(puzzle));

}

     

  
  processLineByLine();

  
