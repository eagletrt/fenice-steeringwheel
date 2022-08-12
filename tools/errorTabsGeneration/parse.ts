const input: string[] = await Deno.readTextFile(Deno.args[0]).then((x) =>
  x.split("\n")
);

const folder = "./newErrors/";

const header = "/* THIS FILE WAS AUTOMATICALLY GENERATED */ ";

const imports = "import Car 1.0 \n \
import Const 1.0 \n \
import QtQuick 2.15 \n \
import QtQuick.Controls 2.15 \n \
import QtQuick.Layouts 1.15\n\n";

const qmlType = "Control { ";
const getError = "function getError(index) { \
    return (centralUnit >>> 0).toString(2).padStart(binaryNLength, '0').slice(0 - index).charAt(0); }";

function writeFile(file: string, content: string) {
  Deno.writeTextFileSync(file, content, { append: true, create: true });
}

interface Topic {
  messageName: string;
  errorFamily: string;
  centralUnit: string;
  type: string;
  index: number;
}
const topics: Map<string, Topic[]> = new Map();

for (const line of input) {
  const words = line.split("_");
  const topic = words[1];
  if (!topics.has(topic)) {
    topics.set(topic, []);
  }
  const topicArray: Topic[] = topics.get(topic) ?? [];
  topicArray.push({
    messageName: words.splice(2).join("_").toLocaleLowerCase(),
    errorFamily: words[1].split(/(?=[A-Z])/).join("_").toLocaleLowerCase(),
    centralUnit: words[1].split(/(?=[A-Z])/)[0].toLocaleLowerCase(),
    type: words[1].split(/(?=[A-Z])/)[1].toLocaleLowerCase(),
    index: topicArray.length + 1,
  } as Topic);
}

for (const topic of topics.keys()) {
  const topicArray: Topic[] = topics.get(topic) ?? [];
  const qml = `${header}
    ${imports}
    ${qmlType}
    readonly property int binaryNLength: 32;\n
    readonly property int nErrors : ${topicArray.length};\n
    property int centralUnit : Car.${topicArray[0].centralUnit}.${topicArray[0].type};\n
    ${getError}
    ${
    topicArray.map((x) =>
      `property int ${x.messageName} : getError(${x.index});`
    ).join("\n")
  }
    padding: 20

    contentItem: ColumnLayout {
        anchors.fill: parent

        Text {
            text: \"${topic}\"
            font: Style.mono.h2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: Style.text
        }

        GridLayout {
            id: errorGrid

            rows: 5
            columns: Math.ceil(nErrors / 5)
            flow: GridLayout.TopToBottom
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    
    ${
    topicArray.map((x) =>
      `ErrorEntry {
            id: ${x.messageName + "_id"}

            errorText: \"${x.messageName.toLocaleUpperCase()}\"
            error: ${x.messageName}
            valid: ${"Car." + x.centralUnit + ".valid"}
            cols: errorGrid.columns
        }`
    ).join("\n")
    }
}
  }
}
    `;
  writeFile(`${folder}${topic}.qml`, qml);
}