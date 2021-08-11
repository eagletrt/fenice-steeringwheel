import QtQuick 2.0
pragma Singleton

QtObject {
    function mod(x, m) {
        const r = x % m;
        return r < 0 ? r + m : r;
    }

}
