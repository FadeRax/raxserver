# raxserver
This was originally a bash script, but I wound up porting it to C just for fun. I'm still hobbling my way around C so I'm sure there's a few things in here that could be improved. Let me know!

## Usage
This program expects a file named `gamemodes` in the same directory. The `gamemodes` file has a VERY primitive key-value format that looks like this:
```
sandbox 3568955956
terrortown 3568955956
prophunt 3577395040
homigrad 3573683063
mapsweepers 3582115250
sledbuildremastered 3587710530
jazztronauts 3600552157
deathrun 3608825484
...
```
`gamemode_name` should be the folder name of the Garry's Mod gamemode, and `workshop_id` should be the last digits of a workshop collection's link.
