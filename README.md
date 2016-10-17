# Node.js bindings for Rasterbar-libtorrent

The base on top of which Porla is built - these Node.js bindings for
Rasterbar-libtorrent are specifically written to support what we need to do in
Porla, but can of course be used elsewhere.

If something is missing, feel free to send a pull request!

## Gotchas

* `add_torrent_params.file_priorities` always returns a copy of the file
  priorities array. To set the priorities, remember to assign the value.
* `bdecode` requires a string, so if you read BDecoded data with `fs.readFile`
  you must remember to pass an encoding so it will return a string instead of
  the raw buffer.

## Known missing

* `add_torrent_params.banned_peers`
* `add_torrent_params.dht_nodes`
* `add_torrent_params.extensions`
