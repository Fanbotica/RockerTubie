
<h1 id="benvenuto-su-rockertubie-github">Benvenuto su RockerTubie GitHub!</h1>
<p><em>Rocker Tubie</em> è un progetto di rover a sei ruote autocostruibile, economico, robusto e modulabile realizzato e presentato al <strong>Maker Faire Europe</strong> che si è tenuto a Roma dal 12 al 14 Ottobre 2018, nel corso del quale ha riscosso un enorme successo di pubblico.<br>
<img src="https://i1.wp.com/www.fanbotica.com/wp-content/uploads/2018/09/Rocker-Tubie-CAD-13.jpg?resize=1024,725&amp;ssl=1" alt="enter image description here"></p>
<p>Il sistema di sospensione del <em>Rocker Tubie</em> è simile a quello dei rover impiegati per le missioni spaziali su Marte.</p>
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

