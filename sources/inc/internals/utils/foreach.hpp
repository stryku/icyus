#pragma once

#define myforeach(container, method, ...) do {for(auto element : ##container) element.##method(__VA_ARGS__); } while(false)

#define myforeachptr(container, method, ...) do {for(auto element : ##container) element->##method(__VA_ARGS__); } while(false)