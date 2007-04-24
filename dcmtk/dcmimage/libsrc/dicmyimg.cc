/*
 *
 *  Copyright (C) 1996-2005, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmimage
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose: DicomCMYKImage (Source)
 *
 *  Last Update:      $Author: braindead $
 *  Update Date:      $Date: 2007/04/24 09:53:47 $
 *  CVS/RCS Revision: $Revision: 1.2 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/dicmyimg.h"
#include "dcmtk/dcmimage/dicmypxt.h"
#include "dcmtk/dcmimgle/diinpx.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiCMYKImage::DiCMYKImage(const DiDocument *docu,
                         const EI_Status status)
  : DiColorImage(docu, status, 4)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        /* number of pixels per plane */
        const unsigned long planeSize = OFstatic_cast(unsigned long, Columns) * OFstatic_cast(unsigned long, Rows);
        switch (InputData->getRepresentation())
        {
            case EPR_Uint8:
                InterData = new DiCMYKPixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
            case EPR_Sint8:
                InterData = new DiCMYKPixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
            case EPR_Uint16:
                InterData = new DiCMYKPixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
            case EPR_Sint16:
                InterData = new DiCMYKPixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
            case EPR_Uint32:
                InterData = new DiCMYKPixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
            case EPR_Sint32:
                InterData = new DiCMYKPixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
                break;
        }
        deleteInputData();
        checkInterData();
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiCMYKImage::~DiCMYKImage()
{
}


/*
 *
 * CVS/RCS Log:
 * $Log: dicmyimg.cc,v $
 * Revision 1.2  2007/04/24 09:53:47  braindead
 * - updated DCMTK to version 3.5.4
 * - merged Gianluca's WIN32 changes
 *
 * Revision 1.1.1.1  2006/07/19 09:16:44  pipelka
 * - imported dcmtk354 sources
 *
 *
 * Revision 1.10  2005/12/08 15:42:20  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.9  2003/12/17 16:34:57  joergr
 * Adapted type casts to new-style typecast operators defined in ofcast.h.
 *
 * Revision 1.8  2002/06/26 16:23:24  joergr
 * Corrected decoding of multi-frame, planar images.
 *
 * Revision 1.7  2001/06/01 15:49:34  meichel
 * Updated copyright header
 *
 * Revision 1.6  2000/03/08 16:21:56  meichel
 * Updated copyright header.
 *
 * Revision 1.5  1999/04/28 13:18:55  joergr
 * Corrected some typos, comments and formatting.
 *
 * Revision 1.4  1998/11/27 14:26:13  joergr
 * Added copyright message.
 * Renamed variable 'Status' to 'ImageStatus' because of possible conflicts
 * with X windows systems.
 *
 * Revision 1.3  1998/05/11 14:52:25  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */
