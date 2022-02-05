liste2 =[""]

print("start")
 
with open('Website.html') as file:
    liste = [line.rstrip() for line in file]

#print(str(len(liste)))
#print("start bereinigen") 
#liste2.append("\"")
for x in liste:
    if   not x.find("//")> (-1) and not x.find("<!--")> (-1):
        x = x.replace("\"", "\\\"")
        x = x.replace("\'", "\\\'")
        liste2.append(x)
#liste2.append("\"")



#print("start write")
f=open("website_one.txt","w")
for y in liste2:
    f.write("send +=\"")
    f.write(y)

    f.write(" \\n \";")
    f.write("\n")
    
f.close()
print("done")