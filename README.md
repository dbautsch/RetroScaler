# RetroScaler

## Disclaimer

This program is work in progress, it does not have all functionality completed yet.

## Introduction

This program has been created to improve scaling options when using older software on modern computers.
An example scenario is using VirtualBox on Windows 11 host with Windows XP guest OS running inside VM.
Windows XP nor even Vista doesn't handle very well DPI scaling, thus when set to value > 100% (more than 96 DPI) the visual result is mediocre by best. It is very often found that software does not offer good enough scaling options and algorithms. The result of an interpolated image is blurry text and this is where RetroScaler comes handy. It offers different scaling options.

## System requirements

The problem with UI scaling of older programs is present on 4k displays when OS scaling is set to 125% or 150%. Because of the amount of data that needs to be pumped through system bus and processed by CPU it is recommended to have highly clocked CPU.

* OS: Windows 10 1609 and never
* graphics card - WDDM 2.0 compatible
* CPU - Intel Core i5 8th generation (or older, overclocked to 4+ GHz) or AMD Ryzen 2600/2700.

## License

License is available in the LICENSE file.
