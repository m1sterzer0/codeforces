import json
import re

with open('contestScrape.json','rb') as fp : db = json.loads(fp.read().decode('utf-8'))
contests = [x for x in db if x['type'] == "contest"]
problems = [x for x in db if x['type'] == "problem" and 'diff' in x and x['diff'] != '???']

problemdb = {}

for p in problems :
    m = re.search(r'contest.(\d+).problem.(.)',p['url'])
    if m :
        pname = m.group(1) + m.group(2)
        pval  = int(p['diff'])
        problemdb[pname] = pval

for c in contests :
    m = re.search(r'contest.(\d+)',c['url'])
    cid = '???'
    if m :
        cid = int(m.group(1))
    c['id'] = cid

#for c in contests[:10] : print(c)
contests.sort(key=lambda x: x['id'])
#for c in contests[:10] : print(c)

ff = open("contestScrape.tsv","wb")
for c in contests :
    cid      = c['id'] 
    title    = c['title']
    roundnum = "???"
    div1     = "NO"
    div2     = "NO"
    m = re.search(r'Codeforces Round #(\d+)', title)
    if m : roundnum = m.group(1)
    m = re.search(r'Div. 1', title)
    if m : div1 = "YES"
    m = re.search(r'Div. 2', title)
    if m : div2 = "YES"
    probstrings = []
    for p in c['problems'] :
        purl = "https://codeforces.com" + p
        diff = "???"
        m = re.search(r'contest.(\d+).problem.(.)',p)
        if m :
            pname = m.group(1) + m.group(2)
            if pname in problemdb :
                diff = str(problemdb[pname])
        probstrings.append(f'=HYPERLINK("{purl}","{diff}")')
    probstring = "\t".join(probstrings)
    outbytes = f'{cid}\t"{title}"\t"{roundnum}"\t"{div1}"\t"{div2}"\t{probstring}\n'.encode('utf-8')
    ff.write(outbytes)
ff.close()