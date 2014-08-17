#!/bin/sh

#only useful for me...
mv /Users/Sean/Downloads/os.txt /Users/Sean/Documents/CrossWorks\ Projects/CalcHack/coCPU_firmware/os.txt
cd /Users/Sean/Documents/CrossWorks\ Projects/CalcHack/coCPU_firmware

ed -s os.txt <<< $',s/AsmPrgm//g\nw'

ed -s os.txt <<< $',s/0/g/g\nw'
ed -s os.txt <<< $',s/1/h/g\nw'
ed -s os.txt <<< $',s/2/i/g\nw'
ed -s os.txt <<< $',s/3/j/g\nw'
ed -s os.txt <<< $',s/4/k/g\nw'
ed -s os.txt <<< $',s/5/l/g\nw'
ed -s os.txt <<< $',s/6/m/g\nw'
ed -s os.txt <<< $',s/7/n/g\nw'
ed -s os.txt <<< $',s/8/o/g\nw'
ed -s os.txt <<< $',s/9/p/g\nw'
ed -s os.txt <<< $',s/A/q/g\nw'
ed -s os.txt <<< $',s/B/r/g\nw'
ed -s os.txt <<< $',s/C/s/g\nw'
ed -s os.txt <<< $',s/D/t/g\nw'
ed -s os.txt <<< $',s/E/u/g\nw'
ed -s os.txt <<< $',s/F/v/g\nw'

ed -s os.txt <<< $',s/g/0x30,/g\nw'
ed -s os.txt <<< $',s/h/0x31,/g\nw'
ed -s os.txt <<< $',s/i/0x32,/g\nw'
ed -s os.txt <<< $',s/j/0x33,/g\nw'
ed -s os.txt <<< $',s/k/0x34,/g\nw'
ed -s os.txt <<< $',s/l/0x35,/g\nw'
ed -s os.txt <<< $',s/m/0x36,/g\nw'
ed -s os.txt <<< $',s/n/0x37,/g\nw'
ed -s os.txt <<< $',s/o/0x38,/g\nw'
ed -s os.txt <<< $',s/p/0x39,/g\nw'
ed -s os.txt <<< $',s/q/0x41,/g\nw'
ed -s os.txt <<< $',s/r/0x42,/g\nw'
ed -s os.txt <<< $',s/s/0x43,/g\nw'
ed -s os.txt <<< $',s/t/0x44,/g\nw'
ed -s os.txt <<< $',s/u/0x45,/g\nw'
ed -s os.txt <<< $',s/v/0x46,/g\nw'

count=$(grep , -o os.txt | wc -l)
count=$((count+8));


rm os.h


echo "#define OS_SIZE "$count >> os.h
echo "const uint8_t os_image[OS_SIZE+2] = {OS_SIZE & 0xFF, (OS_SIZE >> 8) & 0xff," >> os.h
cat os.txt >> os.h
echo "0xD4, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x3F, 0xD4" >> os.h
echo "};" >> os.h

echo "OS-Size in bytes:"
echo $count