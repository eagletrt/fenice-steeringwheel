pragma Singleton
import QtQuick 2.0

QtObject {
    function mod(x, m) {
        const r = x % m;
        return r < 0 ? r + m : r;
    }
}
