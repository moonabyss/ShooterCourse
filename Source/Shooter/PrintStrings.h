#pragma once

#define print(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT(Text), false)
#define printf(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__), false)
