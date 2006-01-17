/*
 * led_checkbox.cpp - class ledCheckBox, an improved QCheckBox
 *
 * Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */


#include "qt3support.h"

#ifdef QT4

#include <QPaintEvent>
#include <QFontMetrics>
#include <QPainter>

#else

#include <qfontmetrics.h>
#include <qpainter.h>

#endif


#include "led_checkbox.h"
#include "embed.h"
#include "gui_templates.h"
#include "spc_bg_hndl_widget.h"


static const QString names[ledCheckBox::TOTAL_COLORS] =
{
	"led_yellow", "led_green"
} ;



ledCheckBox::ledCheckBox( const QString & _text, QWidget * _parent,
							ledColors _color ) :
	QWidget( _parent ),
	m_checked( FALSE ),
	m_text( _text )
{
	if( _color >= TOTAL_COLORS || _color < YELLOW )
	{
		_color = YELLOW;
	}
	m_ledOnPixmap = new QPixmap( embed::getIconPixmap( names[_color]
#ifdef QT4
							.toAscii().constData()
#endif
							 ) );
	m_ledOffPixmap = new QPixmap( embed::getIconPixmap( "led_off" ) );

#ifndef QT4
	setBackgroundMode( Qt::PaletteBackground );
#endif

	setFont( pointSizeF( font(), 7.5f ) );
	setFixedSize( m_ledOffPixmap->width() + 4 +
					QFontMetrics( font() ).width( text() ),
			m_ledOffPixmap->height() );
}




ledCheckBox::~ledCheckBox()
{
	delete m_ledOnPixmap;
	delete m_ledOffPixmap;
}




void ledCheckBox::mousePressEvent( QMouseEvent * _me )
{
	if( _me->button() == Qt::LeftButton )
	{
		toggle();
	}
}
	
	
	
	
void ledCheckBox::toggle( void )
{
	m_checked = !m_checked;
	update();
	emit( toggled( m_checked ) );
}




void ledCheckBox::setChecked( bool _on )
{
	if( _on != isChecked() )
	{
		toggle();
	}
	else
	{
		emit( toggled( m_checked ) );
	}
}




void ledCheckBox::paintEvent( QPaintEvent * )
{
#ifdef QT4
	QPainter p( this );
#else
	QPixmap draw_pm( rect().size() );
	//draw_pm.fill( this, rect().topLeft() );

	QPainter p( &draw_pm, this );
#endif
	p.drawPixmap( 0, 0, specialBgHandlingWidget::getBackground( this ) );

	if( isChecked() == TRUE )
	{
		p.drawPixmap( 0, 0, *m_ledOnPixmap );
	}
	else
	{
		p.drawPixmap( 0, 0, *m_ledOffPixmap );
	}

	p.drawText( m_ledOffPixmap->width() + 2, 8, text() );

#ifndef QT4
	// and blit all the drawn stuff on the screen...
	bitBlt( this, rect().topLeft(), &draw_pm );
#endif
}



#include "led_checkbox.moc"
