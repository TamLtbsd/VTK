/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkOutlineCornerFilter.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Thanks:    Thanks to Sebastien Barre who developed this class.


Copyright (c) 1993-2000 Ken Martin, Will Schroeder, Bill Lorensen 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither name of Ken Martin, Will Schroeder, or Bill Lorensen nor the names
   of any contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "vtkOutlineCornerFilter.h"
#include "vtkOutlineCornerSource.h"
#include "vtkObjectFactory.h"



//------------------------------------------------------------------------------
vtkOutlineCornerFilter* vtkOutlineCornerFilter::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkOutlineCornerFilter");
  if(ret)
    {
    return (vtkOutlineCornerFilter*)ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkOutlineCornerFilter;
}




vtkOutlineCornerFilter::vtkOutlineCornerFilter ()
{
  this->CornerFactor = 0.2;
  this->OutlineCornerSource = vtkOutlineCornerSource::New();
}

vtkOutlineCornerFilter::~vtkOutlineCornerFilter ()
{
  if (this->OutlineCornerSource != NULL)
    {
    this->OutlineCornerSource->Delete ();
    this->OutlineCornerSource = NULL;
    }
}

void vtkOutlineCornerFilter::Execute()
{
  vtkPolyData *output = this->GetOutput();
  
  vtkDebugMacro(<< "Creating dataset outline");

  //
  // Let OutlineCornerSource do all the work
  //

  this->OutlineCornerSource->SetBounds(this->GetInput()->GetBounds());
  this->OutlineCornerSource->SetCornerFactor(this->GetCornerFactor());
  this->OutlineCornerSource->Update();

  output->CopyStructure(this->OutlineCornerSource->GetOutput());

}


void vtkOutlineCornerFilter::ExecuteInformation()
{
  vtkPolyData *output = this->GetOutput();
  
  vtkDebugMacro(<< "Creating dataset outline");

  //
  // Let OutlineCornerSource do all the work
  //
  
  this->vtkSource::ExecuteInformation();

  this->OutlineCornerSource->UpdateInformation();
}


void vtkOutlineCornerFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkDataSetToPolyDataFilter::PrintSelf(os,indent);
  os << indent << "CornerFactor: " << this->CornerFactor << "\n";
}
