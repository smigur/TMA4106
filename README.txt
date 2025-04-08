Pre-forord: Dette er første gang jeg laster opp noe slikt på github, og jeg aner ikke hvordan dette *egentlig* skal gjøres. Om det ikke er mulig å kjøre denne shitten uten videre er det bare å si ifra, om jeg får tid kan jeg prøve å finne ut av det. 

FORORD:

Kjære Nome, 

Dette er et program som er skrevet med utgangspunkt i emnet TDT4102: Prosedyre- og objektorientert programmering. 
I programmet er det brukt emnets egne bibliotek, AnimationWindow. 
Dette biblioteket suger. 
Balle. 
Om du prøver å endre noe og det ikke funker? AnimationWindow. 
Om programmet krasjer på tross av at akkurat dette unntaket hadde sin egen håndtering? AnimationWindow. 
Om programmet forårsaker betydelig minnelekkasje på datamaskinen din?(det skal ikke skje, men man vet aldri) - AnimationWindow. 
Dette biblioteket er mer begrensende enn Alcatraz, mer smertefullt enn testitorsjon, og mer håpløst enn Palestina-konflikten.

Med det sagt - nyt programmet, om du tør å kjøre det på datamaskinen din. Og om du klarer å bruke det. Så lenge det kompilerer. 

Med vennlig hilsen, 
Sigurd Dalen. 
(PS: beklager kjedelig oblig denne gangen. Jeg hadde ikke mer sprit igjen, og jeg fyller ikke 20 før i morgen.)

DOKUMENTASJON - Stokastisk simulering

Overordnet:
Programmet simulerer et utvalg fra en brukervalgt sannsynlighetsfordeling, og viser et histogram som representerer de simulerte verdiene. 

RandomDistribution: 
Klasse for sannsynlighetsfordelinger. Metoden generate() tar inn to parametre og antall simuleringer, og gir en vektor av double-verdier for de ulike simulasjonene. For fordelinger med kun én parameter (i.e. eksponensial), ignoreres den andre verdien. 

csv-håndtering:
Programmet har to funksjoner for filbehandling. saveToCSV() tar inn en vektor av double-verdier og et filnavn, og lagrer verdiene som en fil. readFromCSV() tar inn et filnavn, og returnerer en vektor av double-verdiene i filen. 
saveToCSV lagrer verdiene separert av komma, uten verken header, mellomrom eller nye linjer. readFromCSV krever akkurat denne formateringen. 

GeneratorWindow:
Et vindu som fasiliterer generering av populasjoner. Klassen arver fra AnimationWindow. I vinduet kan brukeren velge en sannsynlighetsfordeling, og sette verdien til de aktuelle parametrene. Ved å trykke på "Simulate"-knappen simuleres verdiene, og lagres som "simulation_results.csv" i prosjektmappa. 
Knappen "Generate histogram" åpner et SimulationWindow med et histogram av dataene, og et antall stolper gitt av slideren under knappen.

SimulationWindow:
Et vindu som inneholder et histogram av dataene i en gitt fil, med et gitt antall stolper. Klassen arver fra AnimationWindow. 
På grunn av limitasjoner innad i AnimationWindow er det ikke mulig å lukke et vindu som er åpnet av et annet, og heller ikke mulig å lukke det andre. Derfor har "Exit"-knappen exit() som callback, og stopper koden fra å kjøre når den er trykket på. 

Verktøy som er brukt:
DeepSeek - Lagde RandomDistribution-klassen de forhåndskonfigurerte instansene. Utenom dette er DeepSeek brukt noe til feilsøking og problemløsning, men med en prompt som hindret den fra å skrive kode. 
