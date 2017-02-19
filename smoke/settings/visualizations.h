#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settingsns.h"

class settingsns::Visualization : public QObject
{
    Q_OBJECT
public:

    static const Visualization &instance();

    float vectorScale;

signals:

public slots:

private:
    explicit Visualization(QObject *parent = 0);

    Visualization(Visualization const&) = delete;
    void operator=(Visualization const&) = delete;
};

#endif // VISUALIZATIONS_H
