#include "filedialog.h"

FileDialog::FileDialog(QObject *parent) {
    setFileMode(QFileDialog::DirectoryOnly);
    setOption(QFileDialog::DontUseNativeDialog,true);
}
