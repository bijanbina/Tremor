#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calibratewindow.h"
#include <opencv/highgui.h>
#include <QtWidgets>
#include <cv.h>
#include <qwt_plot.h>
#include <qwt_legend.h>
#include <qwt_symbol.h>
#include <qwt_color_map.h>
#include <qwt_scale_map.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_text_label.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    char        *FileOpName; //declare FileOpName as IplImage
    IplImage    *imagerd;    //declare imagerd as IplImage

private slots:
    void open_clicked();
    void calibrate_clicked();
    void analysis_clicked();
    void save_clicked();
    void exit_clicked();

private:
    void CreateLayout();
	void CreateMenu();
    void openImage();
    IplImage* doCanny( IplImage* in, double lowThresh, double highThresh, double aperture );
    IplImage* doPyrDown( IplImage* in, int filter);

    QLabel       	*preview;
    QGroupBox       *preview_group;
    QHBoxLayout     *preview_layout;
	QCheckBox    	*chk1;
	QCheckBox    	*chk2;
	QMenuBar		*menu;
	QMenu			*file_menu;
	QMenu			*option_menu;
	QMenu			*help_menu;
	QAction			*a_open;
	QAction			*a_save;
	QAction			*a_exit;
	QAction			*a_calibrate;
	QAction			*a_about;
    QImage       	 imageView;
    QVBoxLayout  	*main_layout;
    QHBoxLayout  	*slider1_layout;
    QLabel       	*radial_label;
    QLabel       	*freq_label;
    QLabel       	*peiod_label;
    QLabel       	*amp_label;
    QWidget      	*Main_Widget;
    QGroupBox       *feature;
    QHBoxLayout  	*surface_layout;
    QVBoxLayout  	*surface2_layout;
    QHBoxLayout  	*option_layout;
    QGridLayout  	*data_layout;
    QGridLayout  	*plot_layout;
    QHBoxLayout  	*progress_layout;
    QHBoxLayout  	*button_layout;
    QPushButton  	*open_btn;
    QPushButton  	*calibrate_btn;
    QPushButton  	*analysis_btn;
    QPushButton  	*save_btn;
    CalibrateWindow *calibrate_window;
	QProgressBar	*progress;
	QwtPlot			*xy_plot;
	QwtPlot			*xt_plot;
	QwtPlot			*yt_plot;
    QwtPlot			*vt_plot;
    QwtPlotGrid     *xy_grid;
    QwtPlotGrid     *xt_grid;
    QwtPlotGrid     *yt_grid;
    QwtPlotGrid     *vt_grid;
    QwtPlotCurve    *xy_curve;
    QwtPlotCurve    *xt_curve;
    QwtPlotCurve    *yt_curve;
    QwtPlotCurve    *vt_curve;
    QwtPlotZoomer   *xy_zoomer;
    QwtPlotZoomer   *xt_zoomer;
    QwtPlotZoomer   *yt_zoomer;
    QwtPlotZoomer   *vt_zoomer;
    IplImage     	*image;
    double        	treshold_1;
    double        	treshold_2;
    double        	erode_count;
    double        	dilate_count;
    char		 	*file_name;
};


#endif // MAINWINDOW_H
