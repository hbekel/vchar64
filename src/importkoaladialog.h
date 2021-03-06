/****************************************************************************
Copyright 2016 Ricardo Quesada

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****************************************************************************/

#pragma once

#include <unordered_map>
#include <QDialog>

namespace Ui {
class ImportKoalaDialog;
}

class ImportKoalaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportKoalaDialog(QWidget *parent = 0);
    ~ImportKoalaDialog();

    const QString& getFilepath() const;

protected:
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    bool validateKoalaFile(const QString& filepath);
    bool processChardef(const std::string& key, quint8 *outKey, quint8* outColorRAM);

    int findColorRAM(const std::vector<std::pair<int,int>>& usedColors, int *outHiColor);

    void normalizeKey(char* key, int hiColorRAM);
    void normalizeWithPaletteStrategy(char* key, int hiColorRAM);
    void normalizeWithNeighborStrategy(char* key, int hiColorRAM);
    bool tryChangeKey(int x, int y, char* key, quint8 mask, int hiColorRAM);
    int getColorByPaletteProximity(int colorIndex, const std::vector<int> &colorsToFind);

    void convert();
    void updateWidgets();

private slots:
    void on_radioD02xManual_clicked();
    void on_radioD02xMostUsed_clicked();
    void on_radioD02xMostUsedHi_clicked();
    void on_radioForegroundMostUsed_clicked();
    void on_radioForegroundMostUsedLow_clicked();
    void on_radioButtonNeighbor_clicked();
    void on_radioButtonPalette_clicked();

    void on_checkBoxGrid_clicked();

    // browse directories
    void on_pushButton_clicked();
    void on_lineEdit_editingFinished();

    void on_pushButtonImport_clicked();
    void on_pushButtonCancel_clicked();


private:

    int _colorRAM;
    Ui::ImportKoalaDialog *ui;
    bool _validKoalaFile;
    QString _filepath;
};
