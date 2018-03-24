#!/usr/bin/python

# 0: striping
# 1: pre-pierce
# 2: cutting
# 3: cooling

layer_jobs = [1, 0, 2, 1]

mode_start = -1
mode_end = -1
mode = -1
cur_layer = -1

mode_start_pos = [0, 0]
mode_end_pos = [0, 0]
cur_pos = [0, 0]

def layer_by_mode(mode):
    if mode == 0:
        return 19
    elif mode == 3:
        return 20
    else:
        pass

def mode_loop(fin, fout, start, end, mode, count):
    for i in range(count):
        fin.seek(start, 0)
        while fin.tell() != end:
            line = fin.readline()
            if line[:3] == 'M07' and (mode == 0 or mode == 3):
                fout.write('M07 U' + str(layer_by_mode(mode)) + '\n')
            else:
                fout.write(line)

# job mode switch between the same layer
def mode_switch(layer_jobs):
    global mode
    if mode == -1:
        if layer_jobs[0]:
            mode = 0
        elif layer_jobs[1]:
            mode = 1
        elif layer_jobs[2]:
            mode = 2
        elif layer_jobs[3]:
            mode = 3
        else:
            mode = -1
    elif mode == 0:
        if layer_jobs[1]:
            mode = 1
        elif layer_jobs[2]:
            mode = 2
        elif layer_jobs[3]:
            mode = 3
        else:
            mode = -1
    elif mode == 1:
        if layer_jobs[2]:
            mode = 2
        elif layer_jobs[3]:
            mode = 3
        else:
            mode = -1
    elif mode == 2:
        if layer_jobs[3]:
            mode = 3
        else:
            mode = -1
    elif mode == 3:
        if layer_jobs[2]:
            mode = 2
        else:
            mode = -1
    else:
        mode = -1

def mode_jump(fin, mode, layer_jobs):
    global mode_start
    if mode == 0:
        if layer_jobs[1] or layer_jobs[2] or layer_jobs[3]:
            fin.seek(mode_start, 0)
            mode_start = -1
        else:
            pass
    elif mode == 1:
        if layer_jobs[2] or layer_jobs[3]:
            fin.seek(mode_start, 0)
            mode_start = -1
        else:
            pass
    elif mode == 2:
        if layer_jobs[3]:
            fin.seek(mode_start, 0)
            mode_start = -1
        else:
            pass
    elif mode == 3:
        mode_start = -1

def extract_xy(line):
    words = line.split()
    # x
    cur_pos[0] = float(words[1][1:])
    # y
    cur_pos[1] = float(words[2][1:])


def update_pos(line):
    if line[:3] == 'G00':
        extract_xy(line)
    elif line[:3] == 'G01':
        extract_xy(line)
    elif line[:3] == 'G02':
        extract_xy(line)
    elif line[:3] == 'G03':
        extract_xy(line)


with open('demo.ngc', 'r') as fin, open('result.ngc', 'w') as fout:
    while True:
        line = fin.readline()
        if not line:
            break
        if line[:3] == 'M07':
            if mode_start == -1:
                mode_start = fin.tell() - len(line)
                words = line.split()
                if int(words[1][1:]) != cur_layer:
                    cur_layer = int(words[1][1:])
                    mode = -1
                mode_switch(layer_jobs)
            else:
                if mode == 0:
                    words = line.split()
                    if int(words[1][1:]) == cur_layer:
                        pass
                    else:
                        mode_end = fin.tell() - len(line)
                        mode_loop(fin, fout, mode_start, mode_end, mode, layer_jobs[mode])
                        mode_jump(fin, mode, layer_jobs)
                elif mode == 1:
                    pass
                elif mode == 2:
                    mode_end = fin.tell() - len(line)
                    mode_loop(fin, fout, mode_start, mode_end, mode, layer_jobs[mode])
                    mode_jump(fin, mode, layer_jobs)
                elif mode == 3:
                    mode_end = fin.tell() - len(line)
                    mode_loop(fin, fout, mode_start, mode_end, mode, layer_jobs[mode])
                    mode_jump(fin, mode, layer_jobs)
        elif line[:3] == 'M02':
            if mode_start == -1:
                fout.write(line)
            else:
                mode_end = fin.tell() - len(line)
                mode_loop(fin, fout, mode_start, mode_end, mode, layer_jobs[mode])
                mode_jump(fin, mode, layer_jobs)
