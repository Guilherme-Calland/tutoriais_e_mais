let p = new Promise((resolve, reject) => {
    let a = 1 + 1
    if(a == 2) {
        resolve('Success')
    } else {
        reject('Failed')
    }
})

p.then((message) => { 
    console.log('This is the then ' + message)
}).catch((message) => {
    console.log('This is the catch ' + message)
})

//then recebe a mesnagem de resolve e executa o que tiver dentro do then caso houver sucesso.

//catch recebe mensagem de reject e executa o que tiver dentro do catch


//no caso de uma  return <algumacoisa>.promise() => 
//se isso nao retornar nulo, a promessa foi cumprida.


function watchTutorialPromise() {
    return new Promise((resolve, reject) => {
        if(userLeft) {
            reject({
                name : 'User left',
                message: ':('
            })
        }else if(userWatchingCatMeme){
            reject({
                name: 'User Watching Cat Meme',
                message: 'tutorial < Cat Meme'
            })
        }else{
            resolve('Thumbs up and subscribe')
        }
    })
}

watchTutorialPromise().then((message) => {
    console.log('Sucess: ' + message)
}).catch((error) => {
    console.log(error.name + ' ' + error.message)
})