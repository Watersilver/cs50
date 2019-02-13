{"filter":false,"title":"dictionary.c","tooltip":"/pset5/speller/dictionary.c","undoManager":{"mark":100,"position":100,"stack":[[{"start":{"row":42,"column":12},"end":{"row":42,"column":16},"action":"remove","lines":["word"],"id":587}],[{"start":{"row":42,"column":12},"end":{"row":42,"column":13},"action":"remove","lines":[" "],"id":588}],[{"start":{"row":42,"column":12},"end":{"row":42,"column":13},"action":"remove","lines":["="],"id":589}],[{"start":{"row":42,"column":12},"end":{"row":42,"column":13},"action":"remove","lines":[" "],"id":590}],[{"start":{"row":42,"column":11},"end":{"row":42,"column":12},"action":"remove","lines":["("],"id":591}],[{"start":{"row":42,"column":41},"end":{"row":42,"column":42},"action":"remove","lines":[")"],"id":592}],[{"start":{"row":42,"column":41},"end":{"row":42,"column":42},"action":"insert","lines":[")"],"id":593}],[{"start":{"row":42,"column":42},"end":{"row":42,"column":49},"action":"remove","lines":[" != EOF"],"id":594}],[{"start":{"row":39,"column":14},"end":{"row":39,"column":15},"action":"insert","lines":[" "],"id":595}],[{"start":{"row":39,"column":15},"end":{"row":39,"column":16},"action":"insert","lines":["="],"id":596}],[{"start":{"row":39,"column":16},"end":{"row":39,"column":17},"action":"insert","lines":[" "],"id":597}],[{"start":{"row":39,"column":17},"end":{"row":39,"column":18},"action":"insert","lines":["N"],"id":598}],[{"start":{"row":39,"column":18},"end":{"row":39,"column":19},"action":"insert","lines":["U"],"id":599}],[{"start":{"row":39,"column":19},"end":{"row":39,"column":20},"action":"insert","lines":["L"],"id":600}],[{"start":{"row":39,"column":20},"end":{"row":39,"column":21},"action":"insert","lines":["L"],"id":601}],[{"start":{"row":15,"column":4},"end":{"row":15,"column":8},"action":"remove","lines":["if ("],"id":602},{"start":{"row":15,"column":4},"end":{"row":15,"column":10},"action":"insert","lines":["return"]}],[{"start":{"row":15,"column":10},"end":{"row":15,"column":11},"action":"insert","lines":[" "],"id":603}],[{"start":{"row":15,"column":42},"end":{"row":22,"column":5},"action":"remove","lines":["","    {","        return true;","    }","    else","    {","        return false;","    }"],"id":604},{"start":{"row":15,"column":42},"end":{"row":15,"column":43},"action":"insert","lines":[";"]}],[{"start":{"row":15,"column":41},"end":{"row":15,"column":42},"action":"remove","lines":[")"],"id":605}],[{"start":{"row":7,"column":17},"end":{"row":10,"column":29},"action":"remove","lines":["","","TrieNode *dictionTrie;","unsigned int wordsInDict = 0;"],"id":606}],[{"start":{"row":6,"column":23},"end":{"row":7,"column":17},"action":"remove","lines":["","#include \"trie.h\""],"id":607}],[{"start":{"row":6,"column":23},"end":{"row":7,"column":17},"action":"insert","lines":["","#include \"trie.h\""],"id":608}],[{"start":{"row":6,"column":23},"end":{"row":7,"column":17},"action":"remove","lines":["","#include \"trie.h\""],"id":609}],[{"start":{"row":17,"column":29},"end":{"row":18,"column":0},"action":"insert","lines":["",""],"id":610},{"start":{"row":18,"column":0},"end":{"row":18,"column":4},"action":"insert","lines":["    "]}],[{"start":{"row":18,"column":4},"end":{"row":18,"column":15},"action":"insert","lines":["wordsInDict"],"id":611}],[{"start":{"row":18,"column":15},"end":{"row":18,"column":16},"action":"insert","lines":[" "],"id":612}],[{"start":{"row":18,"column":16},"end":{"row":18,"column":17},"action":"insert","lines":["="],"id":613}],[{"start":{"row":18,"column":17},"end":{"row":18,"column":18},"action":"insert","lines":[" "],"id":614}],[{"start":{"row":18,"column":18},"end":{"row":18,"column":19},"action":"insert","lines":["0"],"id":615}],[{"start":{"row":18,"column":19},"end":{"row":18,"column":20},"action":"insert","lines":[";"],"id":616}],[{"start":{"row":29,"column":9},"end":{"row":29,"column":10},"action":"remove","lines":["*"],"id":617}],[{"start":{"row":29,"column":13},"end":{"row":29,"column":20},"action":"remove","lines":[" = NULL"],"id":618},{"start":{"row":29,"column":13},"end":{"row":29,"column":15},"action":"insert","lines":["[]"]}],[{"start":{"row":29,"column":14},"end":{"row":29,"column":15},"action":"insert","lines":["4"],"id":619}],[{"start":{"row":29,"column":15},"end":{"row":29,"column":16},"action":"insert","lines":["5"],"id":620}],[{"start":{"row":41,"column":22},"end":{"row":42,"column":0},"action":"insert","lines":["",""],"id":621},{"start":{"row":42,"column":0},"end":{"row":42,"column":8},"action":"insert","lines":["        "]}],[{"start":{"row":42,"column":8},"end":{"row":42,"column":9},"action":"insert","lines":["p"],"id":622}],[{"start":{"row":42,"column":9},"end":{"row":42,"column":10},"action":"insert","lines":["u"],"id":623}],[{"start":{"row":42,"column":10},"end":{"row":42,"column":11},"action":"insert","lines":["t"],"id":624}],[{"start":{"row":42,"column":11},"end":{"row":42,"column":12},"action":"insert","lines":["s"],"id":625}],[{"start":{"row":42,"column":11},"end":{"row":42,"column":12},"action":"remove","lines":["s"],"id":626}],[{"start":{"row":42,"column":10},"end":{"row":42,"column":11},"action":"remove","lines":["t"],"id":627}],[{"start":{"row":42,"column":9},"end":{"row":42,"column":10},"action":"remove","lines":["u"],"id":628}],[{"start":{"row":42,"column":9},"end":{"row":42,"column":10},"action":"insert","lines":["r"],"id":629}],[{"start":{"row":42,"column":10},"end":{"row":42,"column":11},"action":"insert","lines":["i"],"id":630}],[{"start":{"row":42,"column":11},"end":{"row":42,"column":12},"action":"insert","lines":["n"],"id":631}],[{"start":{"row":42,"column":12},"end":{"row":42,"column":13},"action":"insert","lines":["t"],"id":632}],[{"start":{"row":42,"column":13},"end":{"row":42,"column":14},"action":"insert","lines":["f"],"id":633}],[{"start":{"row":42,"column":14},"end":{"row":42,"column":16},"action":"insert","lines":["()"],"id":634}],[{"start":{"row":42,"column":15},"end":{"row":42,"column":17},"action":"insert","lines":["\"\""],"id":635}],[{"start":{"row":42,"column":16},"end":{"row":42,"column":17},"action":"insert","lines":["%"],"id":636}],[{"start":{"row":42,"column":17},"end":{"row":42,"column":18},"action":"insert","lines":["i"],"id":637}],[{"start":{"row":42,"column":18},"end":{"row":42,"column":19},"action":"insert","lines":["\\"],"id":638}],[{"start":{"row":42,"column":19},"end":{"row":42,"column":20},"action":"insert","lines":["n"],"id":639}],[{"start":{"row":42,"column":21},"end":{"row":42,"column":22},"action":"insert","lines":[","],"id":640}],[{"start":{"row":42,"column":22},"end":{"row":42,"column":23},"action":"insert","lines":[" "],"id":641}],[{"start":{"row":42,"column":23},"end":{"row":42,"column":34},"action":"insert","lines":["wordsInDict"],"id":642}],[{"start":{"row":42,"column":35},"end":{"row":42,"column":36},"action":"insert","lines":[";"],"id":643}],[{"start":{"row":32,"column":11},"end":{"row":32,"column":25},"action":"insert","lines":["printf(\"%i\\n\","],"id":644}],[{"start":{"row":32,"column":56},"end":{"row":32,"column":57},"action":"insert","lines":[")"],"id":645}],[{"start":{"row":32,"column":11},"end":{"row":32,"column":25},"action":"remove","lines":["printf(\"%i\\n\","],"id":646}],[{"start":{"row":32,"column":42},"end":{"row":32,"column":43},"action":"remove","lines":[")"],"id":647}],[{"start":{"row":41,"column":22},"end":{"row":42,"column":36},"action":"remove","lines":["","        printf(\"%i\\n\", wordsInDict);"],"id":648}],[{"start":{"row":32,"column":42},"end":{"row":32,"column":43},"action":"insert","lines":[" "],"id":649}],[{"start":{"row":32,"column":43},"end":{"row":32,"column":44},"action":"insert","lines":["!"],"id":650}],[{"start":{"row":32,"column":44},"end":{"row":32,"column":45},"action":"insert","lines":["="],"id":651}],[{"start":{"row":32,"column":45},"end":{"row":32,"column":46},"action":"insert","lines":[" "],"id":652}],[{"start":{"row":32,"column":46},"end":{"row":32,"column":47},"action":"insert","lines":["E"],"id":653}],[{"start":{"row":32,"column":47},"end":{"row":32,"column":48},"action":"insert","lines":["O"],"id":654}],[{"start":{"row":32,"column":48},"end":{"row":32,"column":49},"action":"insert","lines":["F"],"id":655}],[{"start":{"row":40,"column":9},"end":{"row":40,"column":10},"action":"insert","lines":["*"],"id":656}],[{"start":{"row":40,"column":10},"end":{"row":40,"column":11},"action":"insert","lines":["/"],"id":657}],[{"start":{"row":35,"column":8},"end":{"row":35,"column":9},"action":"insert","lines":["*"],"id":658}],[{"start":{"row":35,"column":8},"end":{"row":35,"column":9},"action":"insert","lines":["/"],"id":659}],[{"start":{"row":34,"column":8},"end":{"row":34,"column":9},"action":"insert","lines":["/"],"id":660}],[{"start":{"row":34,"column":9},"end":{"row":34,"column":10},"action":"insert","lines":["/"],"id":661}],[{"start":{"row":34,"column":15},"end":{"row":35,"column":0},"action":"insert","lines":["",""],"id":662},{"start":{"row":35,"column":0},"end":{"row":35,"column":8},"action":"insert","lines":["        "]}],[{"start":{"row":35,"column":41},"end":{"row":36,"column":0},"action":"insert","lines":["",""],"id":663},{"start":{"row":36,"column":0},"end":{"row":36,"column":8},"action":"insert","lines":["        "]}],[{"start":{"row":36,"column":8},"end":{"row":36,"column":9},"action":"insert","lines":["/"],"id":664}],[{"start":{"row":36,"column":9},"end":{"row":36,"column":10},"action":"insert","lines":["/"],"id":665}],[{"start":{"row":35,"column":41},"end":{"row":35,"column":42},"action":"insert","lines":[";"],"id":666}],[{"start":{"row":42,"column":10},"end":{"row":42,"column":11},"action":"remove","lines":["/"],"id":667}],[{"start":{"row":42,"column":9},"end":{"row":42,"column":10},"action":"remove","lines":["*"],"id":668}],[{"start":{"row":37,"column":9},"end":{"row":37,"column":10},"action":"remove","lines":["*"],"id":669}],[{"start":{"row":37,"column":8},"end":{"row":37,"column":9},"action":"remove","lines":["/"],"id":670}],[{"start":{"row":35,"column":42},"end":{"row":36,"column":10},"action":"remove","lines":["","        //"],"id":671}],[{"start":{"row":35,"column":41},"end":{"row":35,"column":42},"action":"remove","lines":[";"],"id":672}],[{"start":{"row":34,"column":15},"end":{"row":35,"column":0},"action":"remove","lines":["",""],"id":673}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":674}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":675}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":676}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":677}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":678}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":679}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":680}],[{"start":{"row":34,"column":15},"end":{"row":34,"column":16},"action":"remove","lines":[" "],"id":681}],[{"start":{"row":34,"column":9},"end":{"row":34,"column":10},"action":"remove","lines":["/"],"id":682}],[{"start":{"row":34,"column":8},"end":{"row":34,"column":9},"action":"remove","lines":["/"],"id":683}],[{"start":{"row":36,"column":51},"end":{"row":36,"column":52},"action":"insert","lines":["\\"],"id":684}],[{"start":{"row":36,"column":52},"end":{"row":36,"column":53},"action":"insert","lines":["n"],"id":685}],[{"start":{"row":36,"column":52},"end":{"row":36,"column":53},"action":"remove","lines":["n"],"id":686}],[{"start":{"row":36,"column":51},"end":{"row":36,"column":52},"action":"remove","lines":["\\"],"id":687}]]},"ace":{"folds":[],"scrolltop":420,"scrollleft":0,"selection":{"start":{"row":36,"column":51},"end":{"row":36,"column":51},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":25,"state":"start","mode":"ace/mode/c_cpp"}},"timestamp":1518826291110,"hash":"701041a9d162757b09a89399fd6fe76c4e61869e"}