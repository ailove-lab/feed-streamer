# OpenGL Animation

Raylib based animation experiments.

- [x] Animation timeline
- [ ] Ffmpeg streaming
- [ ] Scene organisation 
- [ ] Yaml parser for scenes
- [ ] Resource fetcher

## Dependencies

- glfw / raylib
- ffmpeg
- libyaml
- mongoose

## Building

```
cd build
cmake ..
make
./app
```

## Scene

```yaml

font: &Roboto
face: Roboto
   
styles:
  h1: &h1
      font: 
       <<: *Roboto
       size: 32
  h2: &h2 
      font: 
       <<: *Roboto
       size: 24

scenes:
scene 1:
    text 1: 
        <<: *h1   
        value: My message
      pos:
        x: 
            - [  0,-100.0] 
          - [ 60, 100.0] 
          - [240, 100.0]
          - [300,-100.0]
        y: 40
```
   
