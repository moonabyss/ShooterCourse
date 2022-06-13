#pragma once

#define print(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, TEXT(Text), false)
#define printf(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
