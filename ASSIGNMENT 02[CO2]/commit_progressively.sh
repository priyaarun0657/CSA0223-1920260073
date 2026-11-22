#!/usr/bin/env bash
# The assignment requires at least one commit per task (history is checked).
# Run this ONE STEP AT A TIME as you actually work through / re-run each task,
# e.g.  ./commit_progressively.sh 1   then later   ./commit_progressively.sh 2  ...
# First time only:  git init && git branch -M main && git remote add origin <your repo URL>
set -e
case "$1" in
  1) git add Task01 && git commit -m "Q1: precedence, associativity, discount bug, count++ UB (code + screenshots)";;
  2) git add Task02 && git commit -m "Q2: short-circuit evaluation experiments and call counts";;
  3) git add Task03 && git commit -m "Q3: bitwise device register, TODO 1-4 completed, inquiry + array alternative";;
  4) git add Task04 && git commit -m "Q4: ladder vs switch vs lookup, boundary tests, TODO 1 completed";;
  5) git add Task05 && git commit -m "Q5: prime test loops, division counts, do-while/overflow, sieve";;
  6) git add Task06 && git commit -m "Q6: loan repayment schedule, termination, growth, safety limit";;
  7) git add Task07 && git commit -m "Q7: Day-4 design challenge - 6k+-1 redesign and validation";;
  8) git add README.md BUILD_RESULTS.md REPORT_DRAFT.md tools .gitignore commit_progressively.sh && git commit -m "Add README, build results, report draft and helper tools";;
  *) echo "usage: $0 <1-8>"; exit 1;;
esac
git push -u origin main
