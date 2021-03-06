# Cataract Diagnosis
> Projeto da UFRN, disciplina de ITP, para diagnostico de catarata usando linguagem C.

[![NPM Version][npm-image]][npm-url]
[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]

Projeto desenvolvido na linguagem de programação C para disciplina de Introdução em técnicas de programação da Universidade Federal do Rio Grande do Norte (UFRN) 
que através de uma imagem fornecida pelo usuário consegue identificar e diagnosticar catarata, além de fornecer a porcentagem de comprometimento. Os arquivos de imagem
utilizados precisam estar no formato `.ppm`


![](header.png)

## Instalação

Linux:

```sh
git clone https://github.com/YuriGuilherme/cataract-diagnosis.git
```

## Configuração para Desenvolvimento

Pelo tipo de versionamento ser colocado no [Github](github.com), a clonagem do repositório instruído no tópico de instalação já fornece todos os arquivos necessário para o desenvolvimento.  

```sh
cd ./cataract-diagnosis
make clean
make all
```

Para execução teste:

```sh
bin/catdig -i images/imagemexemplo.ppm
```

## Histórico de lançamentos

* 1.0
    * O primeiro lançamento adequado
    * MUDANÇA: Atualização de docs (código do módulo permanece inalterado)
* 0.4
    * MUDANÇA: Comentários de entendimento de código
    * ADD: Adiciona filtros de binarização
    * ADD: Adiciona filtros de binarização
    * CONSERTADO: Retirado `erros` e `warnings` 
* 0.3
    * ADD: Adicionado filtro de escala de cinza
    * MUDANÇA: Adicionado comentários de entendimento de código
* 0.2
    * ADD: Adicionado filtro de escala de cinza
* 0.1
    * Trabalho em andamento

## Meta

Yuri Guilherme – [@YuriGuilherme](https://www.facebook.com/yuri.g.moura) – SeuEmail@exemplo.com

Erick Medeiros – [@thecogmel](https://www.facebook.com/TheCogmel) – erick_mmedeiros@hotmail.com

Distribuído sob a licença MIT. Veja `LICENSE` para mais informações.

[https://github.com/YuriGuilherme/cataract-diagnosis](https://github.com/YuriGuilherme/cataract-diagnosis)

[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics

