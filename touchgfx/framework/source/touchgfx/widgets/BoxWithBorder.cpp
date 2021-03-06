/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.16.1 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/hal/HAL.hpp>

namespace touchgfx
{
void BoxWithBorder::draw(const Rect& area) const
{
    const Rect center = Rect(borderSize, borderSize, getWidth() - (2 * borderSize), getHeight() - (2 * borderSize));
    if (center.isEmpty())
    {
        Rect dirty = area;
        translateRectToAbsolute(dirty);
        HAL::lcd().fillRect(dirty, borderColor, alpha);
        return;
    }

    Rect dirty = area & center;
    Box::draw(dirty);

    if (borderSize == 0)
    {
        return;
    }

    Rect borders[4] =
    {
        Rect(0, 0, getWidth(), borderSize),                                                   // Upper
        Rect(0, getHeight() - borderSize, getWidth(), borderSize),                            // lower
        Rect(0, borderSize, borderSize, getHeight() - (2 * borderSize)),                      // left
        Rect(getWidth() - borderSize, borderSize, borderSize, getHeight() - (2 * borderSize)) // right
    };
    for (int i = 0; i < 4; i++)
    {
        Rect borderDirty = borders[i] & area;
        if (!borderDirty.isEmpty())
        {
            translateRectToAbsolute(borderDirty);
            HAL::lcd().fillRect(borderDirty, borderColor, alpha);
        }
    }
}
} // namespace touchgfx
