/*
    Copyright � 2002, The AROS Development Team. 
    All rights reserved.
    
    $Id$
*/

#include <exec/memory.h>
#include <intuition/icclass.h>
#include <intuition/gadgetclass.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/utility.h>
#ifdef __AROS__
#include <proto/muimaster.h>
#endif

#include "mui.h"
#include "muimaster_intern.h"
#include "support.h"

extern struct Library *MUIMasterBase;

struct MUI_IconListviewData
{
    Object *iconlist;
    Object *vert, *horiz, *button;
    struct Hook hook;
    struct Hook *layout_hook;
};

#ifndef __AROS__
__asm ULONG IconListview_Layout_Function(register __a0 struct Hook *hook, register __a2 Object *obj, register __a1 struct MUI_LayoutMsg *lm)
#else
AROS_UFH3(ULONG,IconListview_Layout_Function,
	AROS_UFHA(struct Hook *, hook,  A0),
	AROS_UFHA(Object *, obj, A2),
	AROS_UFHA(struct MUI_LayoutMsg *, lm,  A1))
#endif
{
    struct MUI_IconListviewData *data = (struct MUI_IconListviewData *)hook->h_Data;
    switch (lm->lm_Type)
    {
	case    MUILM_MINMAX:
		{
		    /* Calulate the minmax dimension of the group,
		    ** We only have a fixed number of children, so we need no NextObject()
		    */
		    WORD maxxxxwidth = 0;
		    WORD maxxxxheight = 0;

		    maxxxxwidth = _minwidth(data->iconlist) + _minwidth(data->vert);
		    if (_minwidth(data->horiz) > maxxxxwidth) maxxxxwidth = _minwidth(data->horiz);
		    lm->lm_MinMax.MinWidth = maxxxxwidth;

		    maxxxxheight = _minheight(data->iconlist) + _minheight(data->horiz);
		    if (_minheight(data->vert) > maxxxxheight) maxxxxheight = _minheight(data->vert);
		    lm->lm_MinMax.MinHeight = maxxxxheight;

		    maxxxxwidth = _defwidth(data->iconlist) + _defwidth(data->vert);
		    if (_defwidth(data->horiz) > maxxxxwidth) maxxxxwidth = _defwidth(data->horiz);
		    lm->lm_MinMax.DefWidth = maxxxxwidth;

		    maxxxxheight = _defheight(data->iconlist) + _defheight(data->horiz);
		    if (_defheight(data->vert) > maxxxxheight) maxxxxheight = _defheight(data->vert);
		    lm->lm_MinMax.DefHeight = maxxxxheight;

		    lm->lm_MinMax.MaxWidth  = MUI_MAXMAX;
		    lm->lm_MinMax.MaxHeight = MUI_MAXMAX;
		    return 0;
		}

		case MUILM_LAYOUT:
		{
		    /* Now place the objects between (0,0,lm->lm_Layout.Width-1,lm->lm_Layout.Height-1)
		    */

		    LONG virt_width;
		    LONG virt_height;
		    LONG vert_width = _minwidth(data->vert);
		    LONG horiz_height = _minheight(data->horiz);
		    LONG lay_width = lm->lm_Layout.Width;
		    LONG lay_height = lm->lm_Layout.Height;
		    LONG cont_width;
		    LONG cont_height;

		    /* layout the virtual group a first time, to determine the virtual width/height */
		    MUI_Layout(data->iconlist,0,0,lay_width,lay_height,0);

		    get(data->iconlist, MUIA_IconList_Width, &virt_width);
		    get(data->iconlist, MUIA_IconList_Height, &virt_height);

		    virt_width += _subwidth(data->iconlist);
		    virt_height += _subheight(data->iconlist);

		    if (virt_width > lay_width && virt_height > lay_height)
		    {
		    	/* We need all scrollbars and the button */
			set(data->vert, MUIA_ShowMe, TRUE); /* We could also overload MUIM_Show... */
			set(data->horiz, MUIA_ShowMe, TRUE);
			set(data->button, MUIA_ShowMe, TRUE);
			cont_width = lay_width - vert_width;
			cont_height = lay_height - horiz_height;
			MUI_Layout(data->vert, cont_width, 0, vert_width, cont_height,0);
			MUI_Layout(data->horiz, 0, cont_height, cont_width, horiz_height, 0);
			MUI_Layout(data->button, cont_width, cont_height, vert_width, horiz_height, 0);
		    } else
		    {
		    	if (virt_height > lay_height)
		    	{
			    set(data->vert, MUIA_ShowMe, TRUE);
			    set(data->horiz, MUIA_ShowMe, FALSE);
			    set(data->button, MUIA_ShowMe, FALSE);

			    cont_width = lay_width - vert_width;
			    cont_height = lay_height;
			    MUI_Layout(data->vert, cont_width, 0, vert_width, cont_height,0);
		    	} else
		    	{
			    if (virt_width > lay_width)
			    {
				set(data->vert, MUIA_ShowMe, FALSE);
				set(data->horiz, MUIA_ShowMe, TRUE);
				set(data->button, MUIA_ShowMe, FALSE);

				cont_width = lay_width;
				cont_height = lay_height - horiz_height;
				MUI_Layout(data->horiz, 0, cont_height, cont_width, horiz_height, 0);
			    } else
			    {
				set(data->vert, MUIA_ShowMe, FALSE);
				set(data->horiz, MUIA_ShowMe, FALSE);
				set(data->button, MUIA_ShowMe, FALSE);

			    	cont_width = lay_width;
			    	cont_height = lay_height;
			    }
		    	}
		    }

		    /* Layout the group a second time, note that setting _mwidth() and _mheight() should be enough, or we invent a new flag */
		    MUI_Layout(data->iconlist,0,0,cont_width,cont_height,0);
		    return 1;
		}
    }
    return 0;
}


#ifndef __AROS__
__asm ULONG IconListview_Function(register __a0 struct Hook *hook, register __a1 void **msg)
#else
AROS_UFH3(ULONG,IconListview_Function,
	AROS_UFHA(struct Hook *, hook,  A0),
	AROS_UFHA(APTR, dummy, A2),
	AROS_UFHA(void **, msg,  A1))
#endif
{
    struct MUI_IconListviewData *data = (struct MUI_IconListviewData *)hook->h_Data;
    int type = (int)msg[0];
    LONG val = (LONG)msg[1];

    switch (type)
    {
	case	1:
		{
		    get(data->vert,MUIA_Prop_First,&val);
		    SetAttrs(data->iconlist,MUIA_IconList_Top, val, MUIA_NoNotify, TRUE, TAG_DONE);
		    break;
		}

	case	2:
		{
		    get(data->horiz,MUIA_Prop_First,&val);
		    SetAttrs(data->iconlist,MUIA_IconList_Left, val, MUIA_NoNotify, TRUE, TAG_DONE);
		    break;
		}
	case	3: nnset(data->horiz, MUIA_Prop_First, val); break;
	case	4: nnset(data->vert, MUIA_Prop_First, val); break;
    }
    return 0;
}

/**************************************************************************
 OM_NEW
**************************************************************************/
static ULONG IconListview_New(struct IClass *cl, Object *obj, struct opSet *msg)
{
    struct MUI_IconListviewData *data;
    //struct TagItem *tags,*tag;
    Object *iconlist = (Object*)GetTagData(MUIA_IconListview_IconList, NULL, msg->ops_AttrList);
    Object *vert,*horiz,*button,*group;

    struct Hook *layout_hook = mui_alloc_struct(struct Hook);
    int usewinborder;

    if (!layout_hook) return NULL;
    usewinborder = GetTagData(MUIA_IconListview_UseWinBorder, FALSE, msg->ops_AttrList);

    if (!usewinborder) button = ScrollbuttonObject, End;
    else button = NULL;

    layout_hook->h_Entry = (HOOKFUNC)IconListview_Layout_Function;

    obj = (Object *)DoSuperNew(cl, obj,
    	MUIA_Group_Horiz, FALSE,
    	Child, group = GroupObject,
	    usewinborder?TAG_IGNORE:MUIA_Group_LayoutHook, layout_hook,
	    Child, iconlist,
	    Child, vert = ScrollbarObject,
		usewinborder?MUIA_Prop_UseWinBorder:TAG_IGNORE, MUIV_Prop_UseWinBorder_Right,
		MUIA_Group_Horiz, FALSE,
		End,
	    Child, horiz = ScrollbarObject,
	    	usewinborder?MUIA_Prop_UseWinBorder:TAG_IGNORE, MUIV_Prop_UseWinBorder_Bottom,
	    	MUIA_Group_Horiz, TRUE,
	    	End,
	    usewinborder?TAG_IGNORE:Child, button,
	    End,
	TAG_DONE);

    if (!obj)
    {
    	mui_free(layout_hook);
	return NULL;
    }

    data = INST_DATA(cl, obj);
    data->vert = vert;
    data->horiz = horiz;
    data->button = button;
    data->iconlist = iconlist;

    data->hook.h_Entry = (HOOKFUNC)IconListview_Function;
    data->hook.h_Data = data;
    data->layout_hook = layout_hook;
    layout_hook->h_Data = data;

    DoMethod(vert, MUIM_Notify, MUIA_Prop_First, MUIV_EveryTime, (IPTR)obj, 4, MUIM_CallHook, (IPTR)&data->hook, 1, MUIV_TriggerValue);
    DoMethod(horiz, MUIM_Notify, MUIA_Prop_First, MUIV_EveryTime, (IPTR)obj, 4, MUIM_CallHook, (IPTR)&data->hook, 2, MUIV_TriggerValue);
    DoMethod(iconlist, MUIM_Notify, MUIA_IconList_Left, MUIV_EveryTime, (IPTR)obj, 4, MUIM_CallHook, (IPTR)&data->hook, 3, MUIV_TriggerValue);
    DoMethod(iconlist, MUIM_Notify, MUIA_IconList_Top, MUIV_EveryTime, (IPTR)obj, 4, MUIM_CallHook, (IPTR)&data->hook, 4, MUIV_TriggerValue);

    return (ULONG)obj;
}

/**************************************************************************
 OM_DISPOSE
**************************************************************************/
static ULONG IconListview_Dispose(struct IClass *cl, Object *obj, Msg msg)
{
    struct MUI_IconListviewData *data = INST_DATA(cl, obj);
    mui_free(data->layout_hook);
    return DoSuperMethodA(cl,obj,msg);
}

/**************************************************************************
 MUIM_Show
**************************************************************************/
static ULONG IconListview_Show(struct IClass *cl, Object *obj, struct MUIP_Show *msg)
{
    struct MUI_IconListviewData *data = INST_DATA(cl, obj);
    LONG top,left,width,height;

    get(data->iconlist, MUIA_IconList_Left, &left);
    get(data->iconlist, MUIA_IconList_Top, &top);
    get(data->iconlist, MUIA_IconList_Width, &width);
    get(data->iconlist, MUIA_IconList_Height, &height);

    SetAttrs(data->horiz, MUIA_Prop_First, left,
			  MUIA_Prop_Entries, width,
			  MUIA_Prop_Visible, _mwidth(data->iconlist),
			  TAG_DONE);


    SetAttrs(data->vert,  MUIA_Prop_First, top,
			  MUIA_Prop_Entries, height,
			  MUIA_Prop_Visible, _mheight(data->iconlist),
			  TAG_DONE);

    return DoSuperMethodA(cl,obj,(Msg)msg);
}

BOOPSI_DISPATCHER(IPTR,IconListview_Dispatcher, cl, obj, msg)
{
    switch (msg->MethodID)
    {
	case OM_NEW: return IconListview_New(cl, obj, (struct opSet *) msg);
	case OM_DISPOSE: return IconListview_Dispose(cl, obj, msg);
	case MUIM_Show: return IconListview_Show(cl, obj, (struct MUIP_Show*)msg);
    }
    return DoSuperMethodA(cl, obj, msg);
}


/*
 * Class descriptor.
 */
const struct __MUIBuiltinClass _MUI_IconListview_desc = { 
    MUIC_IconListview, 
    MUIC_Group, 
    sizeof(struct MUI_IconListviewData), 
    (void*)IconListview_Dispatcher 
};
