Projekt do předmětu ICP

Aplikace pro zobrazení autobusové dopravy v reálném čase.

Autoři: Tomáš Blaha (xblaha31)
	Vojtěch Wawreczka (xwawre00)

Git: https://github.com/tblahagh/ICP_Project

Poznámky:

Aplikace využívá volně dostupnou Third party knihovnu TinyXML pro parsování XML souborů.
Všechny zdrojové soubory knihovny jsou v podadresáři src/tinyxml.
Více o knihovně na http://www.grinninglizard.com/tinyxml/.

Při překladu se vypíší upozornění, které se vztahují na soubory v knihovně TinyXML a proto nebyly opraveny

Adresář src neobsahuje Makefile, protože překlad v adresáři src vyhazoval chyby, které nebyl čas opravit a proto všechny make operace vykonává Makefile v kořenovém adresáři projektu.

Po spuštění samotné aplikace je potřeba vybrat požadovanou mapu. Následně se vykreslí mapa s ulicemi, zastávkami a aktuálními spoji. Po kliknutí na jednotlivé objekty se vykreslí jejich detaily.

U ulice můžeme navíc nastavit hustotu provozu na dané ulici. Střední provoz sníží rychlost na polovinu běžné rychlosti. Hustý provoz na čvrtinu. Ulici můžeme také uzavřít a následně definovat objížďku. U objížďky vybereme trasu klikáním na ulice v mapě (objížďka nesmí obsahovat dvakrát stejnou ulici a musí začínat a končit na koncích uzavřené ulice, může být na sebe navázáno více objížděk, pokud uzavřeme ulici, která je v objízdné trase). Také můžeme definovat zpoždění, které spoj bude kvůli objížďce mít. Pokud objížďku nevybereme bude spoj ukončen, když dorazí k uzavřené ulici. 

U detailu spoje můžeme vidět jízdní řád a aktuální pozici spoje. V mapě máme také vyznačenou trasu spoje. U každého spoje se vypočítává rychlost na základě délky trasy a času podle jízdních řádů. Rychlost také ovlivňuje zpoždění na objížďkách a hustota provozu na ulicích. Vlivem toho se spoj bude opožďovat. Aktualizace polohy spoje na mapě probíhá každou sekundu.

Můžeme také nastavit hodiny na vlastní hodnotu. Při každé inicializaci se spoje vypočítají znova, tedy se berou v úvahu všechny uzavřené ulice a nastavené hustoty provozu. Rychlost můžeme nastavit v intervalu 0 - 50. Při zvýšení rychlosti probíhá aktualizace polohy také každou sekundu.

Přiložená mapa částečně modeluje městskou hromadnou dopravu v Karviné. Obsahuje cca 50 ulic, 30 zastávek a osm autobusových linek s jízdními řády.