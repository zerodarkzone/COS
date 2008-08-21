/*
 o---------------------------------------------------------------------o
 |
 | COS Tracer (proxy)
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Tracer.c,v 1.1 2008/06/27 16:17:17 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Tracer.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

// -----

makclass(Tracer,Proxy);

// -----

static void
trace(struct Tracer *self, SEL sel, OBJ obj[], int pos)
{
  char buf[128];
  cos_trace("<Tracer:%s:%d> sending message %s to self%d (%p)",
            self->file, self->line,
            cos_method_fullName(sel,obj,buf,sizeof buf),
            pos, (void*)self->Proxy.obj);
}

// ----- constructor

defmethod(OBJ, ginitWithLoc, Tracer, Any, (STR)file, (int)line)
  defnext(OBJ, ginitWith, Tracer, Any);
  next_method(self, self2);
  self->file = file;
  self->line = line;
endmethod

// ----- behavior

// rank 1
defmethod(void, gunrecognizedMessage1, Tracer)
  OBJ obj[1]; obj[0]=self->Proxy.obj;

  trace(self,_sel,obj,1);
  next_method(self);
endmethod

// rank 2
defmethod(void, gunrecognizedMessage2, Tracer, Any)
  OBJ obj[2]; obj[0]=self1->Proxy.obj, obj[1]=_2;

  trace(self1,_sel,obj,1);
  next_method(self1,self2);
endmethod

defmethod(void, gunrecognizedMessage2, Any, Tracer)
  OBJ obj[2]; obj[0]=_1, obj[1]=self2->Proxy.obj;

  trace(self2,_sel,obj,2);
  next_method(self1,self2);
endmethod

// rank 3
defmethod(void, gunrecognizedMessage3, Tracer, Any, Any)
  OBJ obj[3]; obj[0]=self1->Proxy.obj, obj[1]=_2, obj[2]=_3;

  trace(self1,_sel,obj,1);
  next_method(self1,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Tracer, Any)
  OBJ obj[3]; obj[0]=_1, obj[1]=self2->Proxy.obj, obj[2]=_3;

  trace(self2,_sel,obj,2);
  next_method(self1,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Any, Tracer)
  OBJ obj[3]; obj[0]=_1, obj[1]=_2, obj[2]=self3->Proxy.obj;

  trace(self3,_sel,obj,3);
  next_method(self1,self2,self3);
endmethod

// rank 4
defmethod(void, gunrecognizedMessage4, Tracer, Any, Any, Any)
  OBJ obj[4]; obj[0]=self1->Proxy.obj, obj[1]=_2, obj[2]=_3, obj[3]=_4;

  trace(self1,_sel,obj,1);
  next_method(self1,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Tracer, Any, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=self2->Proxy.obj, obj[2]=_3, obj[3]=_4;

  trace(self2,_sel,obj,2);
  next_method(self1,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Tracer, Any)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=self3->Proxy.obj, obj[3]=_4;

  trace(self3,_sel,obj,3);
  next_method(self1,self2,self3,self4);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Any, Tracer)
  OBJ obj[4]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=self4->Proxy.obj;

  trace(self4,_sel,obj,4);
  next_method(self1,self2,self3,self4);
endmethod

// rank 5
defmethod(void, gunrecognizedMessage5, Tracer, Any, Any, Any, Any)
  OBJ obj[5]; obj[0]=self1->Proxy.obj, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=_5;

  trace(self1,_sel,obj,1);
  next_method(self1,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Tracer, Any, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=self2->Proxy.obj, obj[2]=_3, obj[3]=_4, obj[4]=_5;

  trace(self2,_sel,obj,2);
  next_method(self1,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Tracer, Any, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=self3->Proxy.obj, obj[3]=_4, obj[4]=_5;

  trace(self3,_sel,obj,3);
  next_method(self1,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Tracer, Any)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=self4->Proxy.obj, obj[4]=_5;

  trace(self4,_sel,obj,4);
  next_method(self1,self2,self3,self4,self5);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Any, Tracer)
  OBJ obj[5]; obj[0]=_1, obj[1]=_2, obj[2]=_3, obj[3]=_4, obj[4]=self5->Proxy.obj;

  trace(self5,_sel,obj,5);
  next_method(self1,self2,self3,self4,self5);
endmethod