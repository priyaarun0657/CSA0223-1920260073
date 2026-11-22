#!/usr/bin/env python3
"""Run shell commands inside a task folder and render the real terminal
transcript ($ command + its output) as a PNG screenshot.

usage: python3 tools/screenshot.py <task_dir> <out.png> "<cmd1>" ["<cmd2>" ...]
"""
import subprocess, sys, os
from PIL import Image, ImageDraw, ImageFont

FONT = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
BOLD = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Bold.ttf"
SIZE, PAD, MAXCOLS = 15, 14, 118

def run(task_dir, cmds):
    lines = []
    for c in cmds:
        lines.append(("$ " + c, "cmd"))
        p = subprocess.run(c, shell=True, cwd=task_dir, capture_output=True,
                           text=True, timeout=300)
        out = (p.stdout or "") + (p.stderr or "")
        for ln in (out.rstrip("\n").split("\n") if out.strip() else []):
            while len(ln) > MAXCOLS:
                lines.append((ln[:MAXCOLS], "out")); ln = "    " + ln[MAXCOLS:]
            kind = "warn" if "warning:" in ln else ("err" if "error:" in ln else "out")
            lines.append((ln, kind))
    return lines

def render(lines, path, title):
    f, fb = ImageFont.truetype(FONT, SIZE), ImageFont.truetype(BOLD, SIZE)
    lh = SIZE + 6
    cw = f.getlength("M")
    w = max(int(max(len(t) for t, _ in lines) * cw) + 2 * PAD, 700)
    h = lh * len(lines) + 2 * PAD + 30
    img = Image.new("RGB", (w, h), (24, 26, 33))
    d = ImageDraw.Draw(img)
    d.rectangle([0, 0, w, 28], fill=(48, 52, 64))
    for i, col in enumerate([(255, 95, 86), (255, 189, 46), (39, 201, 63)]):
        d.ellipse([10 + i * 20, 8, 22 + i * 20, 20], fill=col)
    d.text((80, 6), title, font=f, fill=(190, 195, 210))
    y = 30 + PAD
    colors = {"cmd": (126, 231, 135), "out": (220, 223, 228),
              "warn": (255, 203, 107), "err": (255, 120, 120)}
    for t, k in lines:
        d.text((PAD, y), t, font=fb if k == "cmd" else f, fill=colors[k])
        y += lh
    img.save(path)

if __name__ == "__main__":
    task_dir, out, *cmds = sys.argv[1:]
    lines = run(task_dir, cmds)
    render(lines, out, "T.R Sangeet | 1921260245 | CSA02 Assignment 2 | " + os.path.basename(os.path.abspath(task_dir)))
    print("saved", out, "(%d lines)" % len(lines))
