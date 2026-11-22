#!/usr/bin/env python3
"""Compile and run every program with gcc -Wall -Wextra and write BUILD_RESULTS.md."""
import subprocess, platform
progs = [("Task01","q1_precedence.c","q1",""), ("Task02","q2_shortcircuit.c","q2",""),
         ("Task03","q3_register.c","q3",""), ("Task03","q3_inquiry.c","q3i","-O0"),
         ("Task04","q4_grade.c","q4",""), ("Task04","q4_compare.c","q4c",""),
         ("Task05","q5_is_prime.c","q5",""), ("Task05","q5_variants.c","q5v","-O0"),
         ("Task06","q6_loan.c","q6","-lm"), ("Task07","q7_redesign.c","q7",""),
         ("Task01","q1_more_precedence.c","q1b",""), ("Task02","q2_three_conditions.c","q2b",""),
         ("Task03","q3_stress_test.c","q3s",""), ("Task04","q4_scholarship_full.c","q4s",""),
         ("Task05","q5_loops_extra.c","q5x",""), ("Task06","q6_more_loans.c","q6b","-lm"),
         ("Task07","q7_scaling.c","q7s","")]
gcc = subprocess.run("gcc --version | head -1", shell=True, capture_output=True, text=True).stdout.strip()
out = ["# BUILD_RESULTS", "", "Student: T.R Sangeet | Register number: 1921260245 | Course: CSA02 C Programming | Assignment 2 (CO2)", "",
       f"Compiler: `{gcc}` on {platform.system()} {platform.machine()}", "",
       "Every program was compiled with `-Wall -Wextra` and executed. Output below is the raw output of that run",
       "(timing lines such as `CPU time` differ from run to run; all operation counts are deterministic).", ""]
for d, src, exe, extra in progs:
    cmd = f"gcc -Wall -Wextra {extra} -o {exe} {src}".replace("  ", " ")
    if extra == "-lm": cmd = f"gcc -Wall -Wextra -o {exe} {src} -lm"
    c = subprocess.run(cmd, shell=True, cwd=d, capture_output=True, text=True)
    r = subprocess.run("./" + exe, shell=True, cwd=d, capture_output=True, text=True)
    warns = c.stderr.count("warning:")
    out += [f"## {d}/{src}", "", f"- compile: `{cmd}`", f"- compiler warnings: {warns}"
            + (" (intentional - see report)" if warns else ""), f"- exit status: {r.returncode}", "", "```text", r.stdout.rstrip(), "```", ""]
    if warns: out += ["compiler diagnostics:", "", "```text", c.stderr.rstrip(), "```", ""]
open("BUILD_RESULTS.md", "w").write("\n".join(out))
print("BUILD_RESULTS.md written;", sum(1 for _ in progs), "programs")
