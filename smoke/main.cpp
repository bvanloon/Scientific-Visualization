#include "main.ih"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setQuitOnLastWindowClosed(true);

    setOpenGLVersion(majorOpenGLVersion, minorOpenGLVersion);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}

void setOpenGLVersion(int const majorVersion, int const minorVersion)
{
    QSurfaceFormat glFormat;
    glFormat.setProfile(QSurfaceFormat::CoreProfile);

    glFormat.setVersion(majorVersion, minorVersion);
    glFormat.setOption(QSurfaceFormat::DebugContext);

    QSurfaceFormat::setDefaultFormat(glFormat);
}
