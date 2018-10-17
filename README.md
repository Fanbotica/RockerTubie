---


---

<h1 id="benvenuto-su-rockertubie-github">Benvenuto su RockerTubie GitHub!</h1>
<p><em>Rocker Tubie</em> è un progetto di rover a sei ruote autocostruibile, economico, robusto e modulabile realizzato e presentato al <strong>Maker Faire Europe</strong> che si è tenuto a Roma dal 12 al 14 Ottobre 2018, nel corso del quale ha riscosso un enorme successo di pubblico.<br>
<img src="https://i1.wp.com/www.fanbotica.com/wp-content/uploads/2018/09/Rocker-Tubie-CAD-13.jpg?resize=1024,725&amp;ssl=1" alt="enter image description here"></p>
<p><img src="https://i1.wp.com/www.fanbotica.com/wp-content/uploads/2018/10/stand_fanbotica_05.jpg?resize=768,576&amp;ssl=1" alt="enter image description here"><br>
Il sistema di sospensione del <em>Rocker Tubie</em> è simile a quello dei rover impiegati per le missioni spaziali su Marte.</p>
<p>Le sospensioni sono infatti del tipo a bilanciere, per una migliore stabilità su terreni disconnessi.</p>
<p>Il <em>Rocker Tubie</em> inoltre presenta sei ruote indipendenti da 130 mm x 60 mm ed altrettanti motori a spazzola da 12 V e 107 rpm (giri al minuto).</p>
<p>La presenza di un encoder ad effetto hall su ogni albero motore, consente la rilevazione della esatta posizione, del numero di giri al minuto, e della distanza percorsa da ciascuna ruota.</p>
<p>Nella versione con raccordi stampati in PLA può sopportare carichi fino a 30 kg.</p>
<p>L’elettronica è gestita da microcontrollori Arduino Mega 2560.</p>
<blockquote>
<p>Il Rover Rocker Tubie col suo sistema di sospensioni a bilanciere assicura un costante contatto col terreno di almeno cinque ruote su sei.</p>
</blockquote>
<h1 id="i-files-del-progetto-rocker-tubie-sono-open-source">I files del progetto Rocker tubie sono open source!</h1>
<p>In questo repository sono resi disponibili con <strong>licenza open source GNU</strong> sia le librerie che gli scketch scritti per il rover Rocker Tubie e la sua stazione di controllo, ambedue basati su Arduino Mega 2560 R3.</p>
<h2 id="la-libreria-per-il-modulo-dbh1-driver-dei-motori">La libreria per il modulo DBH1 driver dei motori</h2>
<p>La libreria per il modulo DBH1 da me estesa è basata sul lavoro di David Williams.<br>
Con questa libreria viene offerta la gestione del modulo driver dei motori attraverso i seguenti tipi di comandi:</p>
<blockquote>
<p>Inizializza pin<br>
Avanti<br>
Indietro<br>
Gira a destra<br>
Gira a sinistra<br>
Frena<br>
Folle<br>
Assorbimento Corrente<br>
Avanti solo Motore A<br>
Avanti solo Motore B<br>
Dietro solo Motore A<br>
Dietro solo Motore B<br>
Disabilita solo Motore A<br>
Disabilita solo Motore B<br>
Abilita solo Motore A<br>
Abilita solo Motore B<br>
Abilita Entrambi<br>
Disabilita Entrambi</p>
</blockquote>
<h2 id="sketch-rocker-tubie">Sketch Rocker Tubie</h2>
<p>Si tratta del programma che sovraintende a tutte le funzioni del robot e che viene caricato sul microcontrollore <strong>Arduino Mega 2560 R3</strong> presente a bordo del Rocker Tubie, insieme a tutte le librerie necessarie ad eseguire ogni funzione dal collegamento Wifi alla gestione dei servi e dei motori,</p>
<blockquote>
<p>Wire<br>
Adafruit_PWMServoDriver<br>
SPI<br>
RF24<br>
printf<br>
DBH1</p>
</blockquote>
<p>Da notare che la configurazione del modulo Wifi utilizza i pin arduino Mega</p>
<blockquote>
<p>48 e 53 rispettivamente per CE e CSN.</p>
</blockquote>
<p>L’indirizzo I2C per il modulo di gestione dei servo comandi  è (0x41).<br>
I pin utilizzati dai due Led RGB posizionati sul lato anteriore del Rocker Tubie sono:</p>
<blockquote>
<p>4, 5, 6 (Rosso, Verde, Blu)<br>
44, 45, 46 (Rosso, Verde, Blu).</p>
</blockquote>
<p>il valore di default per la zona morta della Joystick digitale Force 3D Pro è fissato a 30.<br>
I due tipi di sterzata che può compiere il rover sono con movimento intorno all’asse Z coincidente con il baricentro del robot e movimento differenziale con stessa direzione per tutte le ruote e ruote esterne più veloci rispetto a quelle interne.</p>
<h2 id="libreria-stazione-di-controllo">Libreria Stazione di Controllo</h2>
<p>Questa libreria è stata progettata per consentire il completo utilizzo del joystick digitale Logitech Force 3d Pro con lo USB Host Shield 2.0 di Oleg Mazurov e l’Arduino Mega 2560 R3.<br>
Le caratteristiche principali di questo controller sono la codifica digitale a dieci bit per ciascuno dei 12 pulsanti, uno hat switch, uno slider, e la presenza dei tre assi X,Y,Z dei quali quest’ultimo è rotativo e quindi consente il controllo differenziale delle ruote esterni rispetto a quelle interne. La libreria quindi è stata completamente riscritta a partire dal lavoro di Oleg Mazurov.</p>
<h2 id="sketch-stazione-di-controllo">Sketch Stazione di Controllo</h2>
<p>La stazione di controllo per  <a href="https://www.fanbotica.com/portfolio/rocker-tubie-robot-costruito-con-tubi-pvc/">Rocker Tubie</a>  fa parte del progetto <strong>Rocker Tubie</strong> che ho presentato in occasione del <strong>Maker Faire Rome 2018</strong> che si è appena chiuso a Roma.<br>
Le principali caratteristiche di questo sketch per Arduino Mega 2560 R3 sono:</p>
<blockquote>
<ol>
<li>Il parsing della Joystick digitale Logitech Force 3d Pro,</li>
<li>L’invio dei dati grezzi al Rocker Tubie per limitare al massimo ritardi e lag ed assicurare responsività del robot in tutte le fasi di comando.</li>
</ol>
</blockquote>
<p>Le Librerie utilizzate dallo sketch sono le seguenti:</p>
<blockquote>
<p>usbhid<br>
hiduniversal<br>
usbhub<br>
DigitalIO<br>
le3dp_rptparser<br>
RF24.h<br>
printf.h<br>
spi4teensy3<br>
SPI</p>
</blockquote>
<p>I pin utilizzati dal Led RGB posizionato sul lato superiore del box sono:</p>
<blockquote>
<p>4, 5, 6 (Rosso, Verde, Blu)</p>
</blockquote>
<h1 id="sito-web-del-progetto">Sito web del progetto</h1>
<p>Fanbotica è stato ideato come luogo per gli appassionati della  <strong>robotica</strong>, dell’<strong>informatica</strong>  e dell’<strong>intelligenza artificiale.</strong></p>
<p>La sua finalità è quella di condividere con i makers ma anche con i semplici appassionati alla materia, progetti, test e sperimentazioni.</p>
<p>A questo scopo sono resi disponibili molteplici  <strong>tutorial di robotica</strong>  e  <strong>files di spiegazione.</strong> Gli argomenti sono ordinati per categorie di argomenti trattati e grado di difficoltà.</p>
<p><a href="https://www.fanbotica.com">Clicca qui per visitare il sito web del progetto.</a></p>
<h1 id="publication">Publication</h1>
<p>Publishing in StackEdit makes it simple for you to publish online your files. Once you’re happy with a file, you can publish it to different hosting platforms like <strong>Blogger</strong>, <strong>Dropbox</strong>, <strong>Gist</strong>, <strong>GitHub</strong>, <strong>Google Drive</strong>, <strong>WordPress</strong> and <strong>Zendesk</strong>. With <a href="http://handlebarsjs.com/">Handlebars templates</a>, you have full control over what you export.</p>
<blockquote>
<p>Before starting to publish, you must link an account in the <strong>Publish</strong> sub-menu.</p>
</blockquote>
<h2 id="smartypants">SmartyPants</h2>
<p>SmartyPants converts ASCII punctuation characters into “smart” typographic punctuation HTML entities. For example:</p>

<table>
<thead>
<tr>
<th></th>
<th>ASCII</th>
<th>HTML</th>
</tr>
</thead>
<tbody>
<tr>
<td>Single backticks</td>
<td><code>'Isn't this fun?'</code></td>
<td>‘Isn’t this fun?’</td>
</tr>
<tr>
<td>Quotes</td>
<td><code>"Isn't this fun?"</code></td>
<td>“Isn’t this fun?”</td>
</tr>
<tr>
<td>Dashes</td>
<td><code>-- is en-dash, --- is em-dash</code></td>
<td>– is en-dash, — is em-dash</td>
</tr>
</tbody>
</table><h2 id="uml-diagrams">UML diagrams</h2>
<p>You can render UML diagrams using <a href="https://mermaidjs.github.io/">Mermaid</a>. For example, this will produce a sequence diagram:</p>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-o4bR0yzhR3Xakasb" height="100%" width="100%" style="max-width:750px;" viewBox="-50 -10 750 457"><g></g><g><line id="actor60" x1="75" y1="5" x2="75" y2="446" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="0" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="75" dy="0">Alice</tspan></text></g><g><line id="actor61" x1="275" y1="5" x2="275" y2="446" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="200" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="275" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="275" dy="0">Bob</tspan></text></g><g><line id="actor62" x1="475" y1="5" x2="475" y2="446" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="400" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="475" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="475" dy="0">John</tspan></text></g><defs><marker id="arrowhead" refX="5" refY="2" markerWidth="6" markerHeight="4" orient="auto"><path d="M 0,0 V 4 L6,2 Z"></path></marker></defs><defs><marker id="crosshead" markerWidth="15" markerHeight="8" orient="auto" refX="16" refY="4"><path fill="black" stroke="#000000" stroke-width="1px" d="M 9,2 V 6 L16,4 Z" style="stroke-dasharray: 0, 0;"></path><path fill="none" stroke="#000000" stroke-width="1px" d="M 0,1 L 6,7 M 6,1 L 0,7" style="stroke-dasharray: 0, 0;"></path></marker></defs><g><text x="175" y="93" class="messageText" style="text-anchor: middle;">Hello Bob, how are you?</text><line x1="75" y1="100" x2="275" y2="100" class="messageLine0" stroke-width="2" stroke="black" marker-end="url(#arrowhead)" style="fill: none;"></line></g><g><text x="375" y="128" class="messageText" style="text-anchor: middle;">How about you John?</text><line x1="275" y1="135" x2="475" y2="135" class="messageLine1" stroke-width="2" stroke="black" marker-end="url(#arrowhead)" style="stroke-dasharray: 3, 3; fill: none;"></line></g><g><text x="175" y="163" class="messageText" style="text-anchor: middle;">I am good thanks!</text><line x1="275" y1="170" x2="75" y2="170" class="messageLine1" stroke-width="2" stroke="black" marker-end="url(#crosshead)" style="stroke-dasharray: 3, 3; fill: none;"></line></g><g><text x="375" y="198" class="messageText" style="text-anchor: middle;">I am good thanks!</text><line x1="275" y1="205" x2="475" y2="205" class="messageLine0" stroke-width="2" stroke="black" marker-end="url(#crosshead)" style="fill: none;"></line></g><g><rect x="500" y="215" fill="#EDF2AE" stroke="#666" width="150" height="76" rx="0" ry="0" class="note"></rect><text x="496" y="239" fill="black" class="noteText"><tspan x="516" fill="black">Bob thinks a long</tspan></text><text x="496" y="253" fill="black" class="noteText"><tspan x="516" fill="black">long time, so long</tspan></text><text x="496" y="267" fill="black" class="noteText"><tspan x="516" fill="black">that the text does</tspan></text><text x="496" y="281" fill="black" class="noteText"><tspan x="516" fill="black">not fit on a row.</tspan></text></g><g><text x="175" y="319" class="messageText" style="text-anchor: middle;">Checking with John...</text><line x1="275" y1="326" x2="75" y2="326" class="messageLine1" stroke-width="2" stroke="black" style="stroke-dasharray: 3, 3; fill: none;"></line></g><g><text x="275" y="354" class="messageText" style="text-anchor: middle;">Yes... John, how are you?</text><line x1="75" y1="361" x2="475" y2="361" class="messageLine0" stroke-width="2" stroke="black" style="fill: none;"></line></g><g><rect x="0" y="381" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="413.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="75" dy="0">Alice</tspan></text></g><g><rect x="200" y="381" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="275" y="413.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="275" dy="0">Bob</tspan></text></g><g><rect x="400" y="381" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="475" y="413.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle;"><tspan x="475" dy="0">John</tspan></text></g></svg></div>
<p>And this will produce a flow chart:</p>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-zDAH2PJHeMvEFDAB" width="100%" style="max-width: 500.3109359741211px;" viewBox="0 0 500.3109359741211 171.890625"><g transform="translate(-12, -12)"><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath" style="opacity: 1;"><path class="path" d="M119.91170576572816,78.41796875L179.3203125,49.9453125L255.2578125,49.9453125" marker-end="url(#arrowhead375)" style="fill:none"></path><defs><marker id="arrowhead375" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M119.91170576572816,124.41796875L179.3203125,152.890625L234.796875,152.890625" marker-end="url(#arrowhead376)" style="fill:none"></path><defs><marker id="arrowhead376" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M315.1484375,49.9453125L360.609375,49.9453125L408.6013871293077,79.42595738363185" marker-end="url(#arrowhead377)" style="fill:none"></path><defs><marker id="arrowhead377" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M335.609375,152.890625L360.609375,152.890625L408.6013861816871,124.4099806946266" marker-end="url(#arrowhead378)" style="fill:none"></path><defs><marker id="arrowhead378" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="translate(179.3203125,49.9453125)" style="opacity: 1;"><g transform="translate(-30.4765625,-13)" class="label"><foreignObject width="60.953125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel">Link text</span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node" id="A" transform="translate(71.921875,101.41796875)" style="opacity: 1;"><rect rx="0" ry="0" x="-51.921875" y="-23" width="103.84375" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-41.921875,-13)"><foreignObject width="83.84375" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Square Rect</div></foreignObject></g></g></g><g class="node" id="B" transform="translate(285.203125,49.9453125)" style="opacity: 1;"><circle x="-29.9453125" y="-23" r="29.9453125"></circle><g class="label" transform="translate(0,0)"><g transform="translate(-19.9453125,-13)"><foreignObject width="39.890625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Circle</div></foreignObject></g></g></g><g class="node" id="C" transform="translate(285.203125,152.890625)" style="opacity: 1;"><rect rx="5" ry="5" x="-50.40625" y="-23" width="100.8125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-40.40625,-13)"><foreignObject width="80.8125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Round Rect</div></foreignObject></g></g></g><g class="node" id="D" transform="translate(444.96015548706055,101.41796875)" style="opacity: 1;"><polygon points="59.350781250000004,0 118.70156250000001,-59.350781250000004 59.350781250000004,-118.70156250000001 0,-59.350781250000004" rx="5" ry="5" transform="translate(-59.350781250000004,59.350781250000004)"></polygon><g class="label" transform="translate(0,0)"><g transform="translate(-32.9453125,-13)"><foreignObject width="65.890625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Rhombus</div></foreignObject></g></g></g></g></g></g></svg></div>

