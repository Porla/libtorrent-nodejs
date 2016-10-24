const lt = require('../');

const STATEMAP = [
    '',
    'checking_files',
    'downloading_metadata',
    'downloading',
    'finished',
    'seeding',
    'allocating',
    'checking_resume_data'
];

if (process.argv.length != 3)
{
    console.log("usage: node simple_client.js <path>");
    return 1;
}

var session = new lt.session();
var params = {
    save_path: "./",
    ti: new lt.torrent_info(process.argv[2])
};

var handle = session.add_torrent(params);

function printStatus() {
    var status = handle.status();
    var state = STATEMAP[status.state];

    if (status.errc)
    {
        console.error("ERR: %s", status.errc.message);
        return;
    }

    console.log('%s [%s]: rate: %d, state: %s, progress: %d',
        status.name,
        status.info_hash,
        status.download_rate,
        state,
        status.progress);

    if (status.progress >= 1) {
        console.log('finished');
    } else {
        setTimeout(printStatus, 1000);
    }
}

setTimeout(printStatus, 1000);
