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
  let cardNumber = 0;
  let cardNumberCopies = {};
  for await (const card of rl) {
    // console.log('------------------')
    cardNumber++;
    if (cardNumberCopies[cardNumber]) {
      cardNumberCopies[cardNumber] += 1
    } else {
      cardNumberCopies[cardNumber] = 1
    }
    // console.log('cardNumber', cardNumber, cardNumberCopies[cardNumber])
    // Each line in input.txt will be successively available here as `line`.
    const numberOfWinningNumbers = getNumberOfWinningNumbers(card);
    // console.log('numberOfWinningNumbers', numberOfWinningNumbers);
    if (numberOfWinningNumbers === 0) {
      
    } else {
      for (let i = 1; i <= numberOfWinningNumbers; i++) {
        let newCardNumber = cardNumber + i;
        if (cardNumberCopies[newCardNumber]) {
          cardNumberCopies[newCardNumber] += cardNumberCopies[cardNumber]
        } else {
          cardNumberCopies[newCardNumber] = cardNumberCopies[cardNumber]
        } 
      }
    }
    sum += cardNumberCopies[cardNumber]
    
  }
  console.log(cardNumberCopies);
  console.log(sum)
}

processLineByLine();



function getNumberOfWinningNumbers(card) {
  let numberOfWinningNumbers = 0;
  const winningNumbers = new Map(card.split(':')[1].split('|')[0].split(' ').filter(e => e !== '').map(e => [e, true]));
  card.split(':')[1].split('|')[1].split(' ').filter(e => e !== '').forEach(e => {
    if (winningNumbers.has(e)) {
      numberOfWinningNumbers++;
    }
  });
  return numberOfWinningNumbers;
}