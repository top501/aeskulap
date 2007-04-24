/*
 *
 *  Copyright (C) 2005, OFFIS
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
 *  Module:  dcmsr
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose:
 *    classes: DSRXRayRadiationDoseSRConstraintChecker
 *
 *  Last Update:      $Author$
 *  Update Date:      $Date$
 *  CVS/RCS Revision: $Revision$
 *  Status:           $State$
 *
 *  CVS/RCS Log at end of file
 *
 */


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrxrdcc.h"


DSRXRayRadiationDoseSRConstraintChecker::DSRXRayRadiationDoseSRConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRXRayRadiationDoseSRConstraintChecker::~DSRXRayRadiationDoseSRConstraintChecker()
{
}


OFBool DSRXRayRadiationDoseSRConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRXRayRadiationDoseSRConstraintChecker::isTemplateSupportRequired() const
{
    return OFFalse;
}


const char *DSRXRayRadiationDoseSRConstraintChecker::getRootTemplateIdentifier() const
{
    return NULL;
}


DSRTypes::E_DocumentType DSRXRayRadiationDoseSRConstraintChecker::getDocumentType() const
{
    return DT_XRayRadiationDoseSR;
}


OFBool DSRXRayRadiationDoseSRConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                         const E_RelationshipType relationshipType,
                                                                         const E_ValueType targetValueType,
                                                                         const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.X-2 in DICOM Supplement 94 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_Num)   ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_UIDRef)    || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Image)    || (targetValueType == VT_Composite) || (targetValueType == VT_Container);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_hasObsContext) && ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) ||
            (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)   || (targetValueType == VT_Num)   ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_UIDRef) || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Composite);
        }
        /* row 3 of the table */
        else if ((relationshipType == RT_hasAcqContext) && ((sourceValueType == VT_Container) || (sourceValueType == VT_Image) ||
            (sourceValueType == VT_Composite)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)   || (targetValueType == VT_Num)   ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_UIDRef) || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Container);
        }
        /* row 4 of the table */
        else if (relationshipType == RT_hasConceptMod)
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code);
        }
        /* row 5 of the table */
        else if ((relationshipType == RT_hasProperties) && ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) ||
            (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_Num)   ||
                     (targetValueType == VT_DateTime) || (targetValueType == VT_UIDRef)    || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Image)    || (targetValueType == VT_Composite) || (targetValueType == VT_Container);
        }
        /* row 6 of the table */
        else if ((relationshipType == RT_inferredFrom) && ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) ||
            (sourceValueType == VT_Num)))
        {
            result = (targetValueType == VT_Text)      || (targetValueType == VT_Code)   || (targetValueType == VT_Num)   ||
                     (targetValueType == VT_DateTime)  || (targetValueType == VT_UIDRef) || (targetValueType == VT_Image) ||
                     (targetValueType == VT_Composite) || (targetValueType == VT_Container);
        }
    }
    return result;
}


/*
 *  CVS/RCS Log:
 *  $Log$
 *  Revision 1.1  2007/04/24 09:53:38  braindead
 *  - updated DCMTK to version 3.5.4
 *  - merged Gianluca's WIN32 changes
 *
 *  Revision 1.1.1.1  2006/07/19 09:16:43  pipelka
 *  - imported dcmtk354 sources
 *
 *
 *  Revision 1.2  2005/12/08 15:48:26  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.1  2005/11/30 12:06:26  joergr
 *  Added support for X-Ray Radiation Dose SR documents.
 *
 *
 */
