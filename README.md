# Basic-Linux-Unix-shell

A clone of linux shell. The shell can execute 5 external and 5 internal commands.Two options for each command have also been implemented. Error handling is also done. Shell can execute following external commands:
<ol>
<li>cat ,options: -E,-n</li>
<li>date ,options: -u,-r</li>
<li>ls ,options: -i, -m</li>
<li>mkdir ,options: -p,-v</li>
<li>rm ,options: -i, -v</li>
</ol>
and following internal commands:
<ol>
<li>cd ,options: -L, -P</li>
<li>pwd ,options: -L, -P</li>
<li>echo ,options: -n, -e</li>
<li>history ,options: -w, -s</li>
<li>exit [exitcode]</li>
</ol>
Please refer to man pages for understanding function of each flag of every function.
<h1>Installation Guide</h1>
In linux,
<ol>
<li>Dowload the zip file.</li>
<li>Extract it in a suitable directory.</li>
<li>Open the terminal in the same directory where extracted files are present.</li>
<li>Type and enter 'make externalbin'.</li>
<li>Type and enter 'make compile_link'.</li>
<li>Type and enter 'make run'.</li>
<li>Interact with the shell by entering any of the mentioned commands like command [-option] </li>
</ol>
