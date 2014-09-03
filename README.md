JVTerm
======
JVIrc-like extrêmement basique en ncurses.

Demande :
- ncurses/ncursesw (les deux ou seulement la deuxième, je sais pas).
- curlpp.
- boost.regex.

Si vous avez GCC > 4.9 vous pouvez compiler sans boost, en remplaçant tout les boost:: dans jvcPostManager.cpp et jvcPostManager.hpp par std::, et remplacer l'include de boost dans le .hpp par l'include de &lt;regex&gt;.

Pour l'instant, il faut lancer le programme avec en 1er paramètre le formulaire de réponse du topic, second le pseudo et troisème le mot de passe.  
F10 pour quitter.

Pour curlpp si vous avez la flemme vous pouvez télécharger une version amd64 ici http://www.blablacraft.fr/upload/libcurlpp.zip.
