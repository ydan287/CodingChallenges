function removeLeadingZeroes(str) {
  let i = 0;
  while (str[i] === '0' && i < str.length-1) {
    i++;
  }
  return str.slice(i);
}

function blink(stone) {
  if (stone === '0') {
    return ['1'];
  } 

  if (stone.length % 2 === 0) {
    const mid = stone.length / 2;
    const left = stone.slice(0, mid);
    const right = removeLeadingZeroes(stone.slice(mid));
    return [left, right];
  } 

  return [(Number(stone) * 2024).toString()];
}

let memo = new Map();

function recursive(stone, blinksLeft) {
  if (blinksLeft === 0) {
    return 1;
  }

  if (memo.has(key(stone, blinksLeft))) {
    return memo.get(key(stone, blinksLeft));
  }

  let stonesAfterBlink = blink(stone);
  let result = 0;
  stonesAfterBlink.forEach(stone => {
      result += recursive(stone, blinksLeft - 1);
    });
    memo.set(key(stone,blinksLeft), result);
  return result;
} 

function key(stone, blink) {
  return `${stone}-${blink}`;
}

function solution1(arrangement) {
  let result = 0;
  let stones = arrangement.split(' ');
  stones.forEach(stone => {
    result += recursive(stone, 75);
  });
  return result;
}

function solution2(arrangement) {
  let numberOfBlinks = 75;
  let stones = arrangement.split(' ');
  console.log(`initial arrangement: ${stones}`);
  result = 0;
  stones.forEach(origStone => {
    const blinkMap = new Map();
    let queue = [{stone: origStone, blinks: 0}]
    while (!blinkMap.get(key(origStone,numberOfBlinks))) {
      
      let {stone, blinks} = queue.shift();
      if (stone === origStone) {
        console.log(`stone: ${stone}, blinks: ${blinks}, queue: ${queue.length} map: ${blinkMap.size} score: ${blinkMap.get(key(origStone,blinks-1))}`);
      }
      
      if (blinkMap.get(key(stone,blinks))) {
        if (stone === origStone) {
          queue.push({stone, blinks: blinks + 1});
        }
        continue;
      }

      if (blinks === 0) {
        blinkMap.set(key(stone,0), 1);
        queue.push({stone, blinks: blinks + 1});
        continue;
      }

      let stonesAfterBlink = blink(stone);
      
      if (stonesAfterBlink.every(stone => blinkMap.get(key(stone,blinks-1)))) {
        let sum = 0;
        stonesAfterBlink.forEach(stone => {
          sum += blinkMap.get(key(stone,blinks-1));
        });
        blinkMap.set(key(stone,blinks), sum);
        queue.push({stone, blinks: blinks + 1});
      } else {
        stonesAfterBlink.forEach(stone => {
          if (!blinkMap.get(key(stone,blinks-1))) {
            queue.push({stone, blinks: blinks -1});
          }
        });
        queue.push({stone, blinks: blinks});
      }
    }
    result += blinkMap.get(key(origStone,numberOfBlinks));
  })
  

  return result;
}

let map = new Map();
console.log("🚀 ~ :", solution1("0 7 6618216 26481 885 42 202642 8791"))
