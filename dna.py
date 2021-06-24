import sys
import csv
import re
dna = {}
with open(sys.argv[1], "r") as file:
      # Create DictReader
      reader = csv.DictReader(file)
      headers = reader.fieldnames[1:]
      for row in reader:
          ans=[]
          for key in list(row.keys())[1:]:
              ans.append(int(row[key]))
          dna[row["name"]]=ans
seq = open(sys.argv[2], 'r')
seq=seq.read()
count={}
for i in headers:
     r = re.compile(i)
     index=[[m.start(),m.end()] for m in r.finditer(seq)]
     maxx = -1
     length=len(i)
     for j in range(len(index)):
         cur = index [j][-1]
         add=1
         for k in range(j+1,len(index)):
             if index[k][-1]-cur==length:
                 add+=1
                 cur =  index[k][-1]
             else:
                break
         if add>maxx:
             maxx=add
         else:
             maxx=maxx
     count[i]=maxx

ans="No match"
for i in dna.keys():
    if dna[i]==list(count.values()):
        ans=i
        break
print(ans)



