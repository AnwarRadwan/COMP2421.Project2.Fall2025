# Football Tournament - Real Runner-Up System

## 📌 Description
This project simulates a knockout football tournament to determine both the champion and the real runner-up.

Teams compete in rounds where only the winner advances to the next stage. The winner of each match is determined based on the round number:
- In odd rounds → the team with the smaller ID wins
- In even rounds → the team with the larger ID wins

If the number of teams in a round is odd, the last team automatically advances to the next round and is placed at the beginning of the list.

After determining the champion, a second tournament is conducted using all teams that lost against the champion. These teams are reordered in reverse and compete again using the same rules to determine the real runner-up.

---

## 🧠 Algorithm Overview
1. Read input test cases until `-9999`
2. Run knockout tournament to determine the champion
3. Collect all teams that lost to the champion
4. Reverse the losing teams list
5. Run a second tournament to determine the real runner-up

---

## ⚙️ Match Rules
- Odd round → smaller ID wins
- Even round → larger ID wins

---

## 📥 Input Format
Each test case is given in a single line:

n id1 id2 id3 ... idn


Example:
5 4 3 6 9 2


Input ends with:
-9999


---

## 📤 Output Format
For each test case, print:

---

## 🛠️ Implementation Details
- Data Structures: Linked List / Queue (based on implementation)
- Tournament simulation using iterative rounds
- Custom comparison logic based on round number
- Secondary tournament for runner-up determination

---

## 🚀 How to Compile & Run
```bash
gcc main.c -o tournament
./tournament
