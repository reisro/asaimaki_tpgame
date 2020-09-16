// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiItem.h"

FPrimaryAssetId UAsaiMakiItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(ItemType, GetFName());
}
